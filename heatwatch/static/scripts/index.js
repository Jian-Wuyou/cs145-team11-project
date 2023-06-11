window.onload = async () => {
    const current = document.getElementById("current");
    const past = document.getElementById("past");
    let readingUpdate; // timed function

    const clearChart = () => {
        HI_dps.length=0; T_dps.length=0; H_dps.length=0;
        HI_dps_agg.length=0; T_dps_agg.length=0; H_dps_agg.length=0;
        readings.length=0; readings_agg.length=0;
        chart.render();
    }

    const updateReadings = () => {
        readingUpdate = setInterval(async ()=>{
            console.log(`lastreading:${lastReading}`)
            await updateChart()
        }, updateInterval);
    }

    current.addEventListener('click', async () => {
        current.classList.add("selected");
        past.classList.remove("selected");
        clearInterval(readingUpdate);
        clearChart();
        updateReadings();
    });

    past.addEventListener('click', async () => {
        past.classList.add("selected");
        current.classList.remove("selected");
        clearInterval(readingUpdate);
        clearChart();
        await summaryChart();
    });

    updateReadings();
}