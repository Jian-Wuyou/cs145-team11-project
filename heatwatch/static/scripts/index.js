window.onload = async () => {

    const bisect_left = function(a, x, key=null, lo=0, hi=null) {
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

    const updateInterval = 5000; // just increase if it's causing lag
    let maxTime = 20; // only keeps readings from the past maxTime seconds
    let readings = []; // array of [time, HI, T, RH] tuples
    let lastReading = Date.now() - maxTime * 1E3; // time, in milliseconds, of last reading

    let HI_dps = [];
    const chart = new CanvasJS.Chart("chart", {
        zoomEnabled: true,
        title :{
            text: "Heat Index vs Time"
        },
        data: [{
            type: "line",
            dataPoints: HI_dps
        }]
    });

    const updateChart = async function(maxTime) {
        let cutoff = Date.now() - maxTime * 1E3;
        // fetch data after lastReading
        const request = new Request(`${domain}/readings`, {
            method: "POST",
            headers: {
                'Content-Type': 'application/json'
            },
            body: JSON.stringify({
                "time": {
                    "min": lastReading
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

        lastReading = data.last;        // Update lastReading for next fetch request
        readings.push(...data.data);    // Extend readings with newly fetched data
        for(dp of data.data) {          // Extend Heat Index datapoints
            HI_dps.push({
                x: new Date(dp[0]),
                y: dp[1]
            });
        }

        // Remove the readings from before the cutoff
        let idx = bisect_left(readings, cutoff, (a, x) => { return a[x][0]; });
        readings.splice(0, idx);
        HI_dps.splice(0, idx);

        chart.render();
    };
    
    await updateChart(maxTime);
    setInterval(async () => {
        await updateChart(maxTime)
    }, updateInterval);
}