let maxTime = 60; // only keeps readings from the past maxTime seconds
const maxTime_agg = 604800000; // only keeps readings from the past 7 days

let readings = []; // array of [time, HI, T, RH] tuples
let readings_agg = []; // array of aggregated [time, HI, T, RH] tuples 
let lastReading = Date.now() - maxTime * 1E3; // time, in milliseconds, of last reading 

let HI_dps = []; let T_dps = []; let H_dps = [];   // datapoints for real time readings
let HI_dps_agg = []; let T_dps_agg = []; let H_dps_agg = [];  // datapoints for aggregated readings 

// initialize chart
const chart = new CanvasJS.Chart("chart", {
    zoomEnabled: true,
    title :{
        text: "Heat Index vs Time",
        fontFamily: "system-ui,-apple-system,system-ui,Helvetica Neue,Helvetica,Arial,sans-serif",
        fontWeight: 600
    },
    axisY:{
        minimum: 0,
        interval: 10
    },
    data: [
        {
            type: "spline",
            showInLegend: true,
            legendText: "Temperature",
            // lineColor: "#fbff1d50",
            // color: "#fbff1d50",
            // fillOpacity: .4
        },
        {
            type: "spline",
            showInLegend: true,
            legendText:"Humidity",
            // lineColor: "#1db7ff45",
            // color: "#1db7ff45",
            // fillOpacity: .3
        },
        {
            type: "spline",
            showInLegend: true,
            legendText:"Heat Index",
            // lineColor: "#910000de",
            // color: "#910000de"
        }
    ]
});

// get aggregated readings then update chart
const summaryChart = async function(){
    let cutoff = Date.now() - maxTime_agg; // 7 days ago

    // fetch data after lastReading
    const request = new Request(`/summary`, {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            "time": {
                "min": cutoff 
            }
        })
    });  

    const response = await fetch(request);
    let data;

    if(response.status == 200) {
        data = await response.json();
    } else {
        console.error(`Failed to fetch data (body: ${request.body})`);
        return;
    }

    readings.push(...data.data);    // Extend readings with newly fetched data
    for(dp of data.data) {          // Extend Heat Index datapoints
        HI_dps_agg.push({
            x: new Date(dp[0]),
            y: dp[1],
            markerSize: 5
        });
        H_dps_agg.push({
            x: new Date(dp[0]),
            y: dp[3],
            markerSize: 5
        });
        T_dps_agg.push({
            x: new Date(dp[0]),
            y: dp[2],
            markerSize: 5,
        });
    }

    // replace chart datapoints
    chart.options.data[0].dataPoints = T_dps_agg;
    chart.options.data[1].dataPoints = H_dps_agg;
    chart.options.data[2].dataPoints = HI_dps_agg;

    chart.render();
}

// get real time readings then update chart
const updateChart = async function() {
    let cutoff = Date.now() - maxTime * 1E3
    // fetch data after lastReading
    const request = new Request(`/readings`, {
        method: "POST",
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify({
            "time": {
                "min":lastReading 
            }
        })
    }); 

    const response = await fetch(request);
    let data;

    if(response.status == 200) {
        data = await response.json();
    } else {
        console.error(`Failed to fetch data (body: ${request.body})`);
        return;
    }

    if (!data.last) // no new reading in database; don't update
        return 

    lastReading = data.last;        // Update lastReading for next fetch request
    console.log(data.data)
    readings.push(...data.data);    // Extend readings with newly fetched data
    for(dp of data.data) {          // Extend Heat Index datapoints
        HI_dps.push({
            x: new Date(dp[0]),
            y: dp[1],
            markerSize: 5
        });
        H_dps.push({
            x: new Date(dp[0]),
            y: dp[3],
            markerSize: 5
        });
        T_dps.push({
            x: new Date(dp[0]),
            y: dp[2],
            markerSize: 5
        });
    }

    // Remove the readings from before the cutoff
    let idx = bisect_left(readings, cutoff, (a, x) => { return a[x][0]; });
    readings.splice(0, idx);
    HI_dps.splice(0, idx);
    H_dps.splice(0, idx);
    T_dps.splice(0, idx);

    // replace chart datapoints
    chart.options.data[0].dataPoints = T_dps;
    chart.options.data[1].dataPoints = H_dps;
    chart.options.data[2].dataPoints = HI_dps;

    chart.render();
};

const bisect_left = function (a, x, key=null, lo=0, hi=null) {
    if(lo < 0) {
        throw new Error('lo must be non-negative');
    }
    if(hi == null) {
        hi = a.length;
    }
    if(key == null) {
        key = (a, x) => { return a[x]; }
    }
    while(lo < hi){
        let mid = (lo+hi) >> 1;

        if(key(a, mid) < x){
            lo = mid+1;
        } else {
            hi = mid;
        }
    }
    return lo;
}