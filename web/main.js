const cachedIds = [];
const chartContext = document.getElementById('weather_chart').getContext('2d');
const chart = new Chart(chartContext, {
  type: 'line',
  data: {
    labels: [],
    datasets: [
      {
        label: 'Temperature (° C)',
        data: [],
        borderColor: 'rgb(255, 99, 132)',
        cubicInterpolationMode: 'monotone',
      },
      {
        label: 'Humidity',
        data: [],
        borderColor: 'rgb(255, 159, 64)',
        cubicInterpolationMode: 'monotone',
      },
    ],
  },
});

fetchData = async (fullFetch = false) => {
  const weatherRequest = await fetch('http://localhost:8080/weather');
  const jsonResponse = await weatherRequest.json();

  jsonResponse
    .filter((obj) => !cachedIds.includes(obj.id))
    .forEach(({ id, createdAt, temperature, humidity }) => {
      createdAt = new Date(createdAt);

      cachedIds.push(id);

      const hoursString = ('0' + createdAt.getHours()).slice(-2);
      const minutesString = ('0' + createdAt.getMinutes()).slice(-2);
      const secondsString = ('0' + createdAt.getSeconds()).slice(-2);

      chart.data.labels.push(`${hoursString}:${minutesString}:${secondsString}`);
      chart.data.datasets[0].data.push(temperature);
      chart.data.datasets[1].data.push(humidity);
      chart.update();
    });
}

fetchData(true);
setInterval(fetchData, 5000);
