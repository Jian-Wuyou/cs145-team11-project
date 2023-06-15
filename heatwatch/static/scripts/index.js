window.onload = async () => {
    const current = document.getElementById("current");
    const past = document.getElementById("past");
    const cutoff_span = document.getElementById("cutoff-span");
    const cutoff = document.getElementById("cutoff");
    let readingUpdate; // timed function

    const clearChart = () => {
        HI_dps.length=0; T_dps.length=0; H_dps.length=0;
        HI_dps_agg.length=0; T_dps_agg.length=0; H_dps_agg.length=0;
        readings.length=0; readings_agg.length=0;
        chart.render();
    }

    const updateInterval = 1000; // just increase if it's causing lag

    const updateReadings = () => {
        readingUpdate = setInterval(async ()=>{
            console.log(`lastreading:${lastReading}`)
            await updateChart()
        }, updateInterval);
    }

    cutoff.addEventListener('change', () => {
        if(cutoff.value != "") {
            maxTime = cutoff.value;
        } else {
            maxTime = 60;
        }
        lastReading = Date.now() - maxTime * 1E3;
        clearInterval(readingUpdate);
        clearChart();
        updateReadings();
    })

    current.addEventListener('click', async () => {
        cutoff_span.style.display = "inline";
        current.classList.add("selected");
        past.classList.remove("selected");
        clearInterval(readingUpdate);
        clearChart();
        updateReadings();
    });

    past.addEventListener('click', async () => {
        cutoff_span.style.display = "none";
        past.classList.add("selected");
        current.classList.remove("selected");
        clearInterval(readingUpdate);
        clearChart();
        await summaryChart();
    });

    updateReadings();
}