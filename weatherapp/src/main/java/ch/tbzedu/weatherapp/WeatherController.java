package ch.tbzedu.weatherapp;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
public class WeatherController {
    private final WeatherRepository weatherRepository;

    public WeatherController(WeatherRepository weatherRepository) {
        this.weatherRepository = weatherRepository;
    }

    @GetMapping("/weather")
    List<Weather> getWeather() {
        return weatherRepository.findAll();
    }

    @PostMapping("/weather")
    Weather createWeather(@RequestBody Weather weather) {
        return weatherRepository.save(weather);
    }
}
