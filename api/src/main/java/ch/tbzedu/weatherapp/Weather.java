package ch.tbzedu.weatherapp;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;
import org.hibernate.annotations.CreationTimestamp;

import javax.persistence.*;
import java.sql.Timestamp;

@Entity
@Getter
@Setter
@Table(name = "Weather")
@ToString
public class Weather {
    @Column(name = "id", unique = true, nullable = false)
    @GeneratedValue(strategy= GenerationType.AUTO)
    @Id
    private Long id;

    @Column(name = "created_at", nullable = false)
    @CreationTimestamp
    private Timestamp createdAt;

    @Column(name = "temperature", nullable = false)
    private float temperature;

    @Column(name = "humidity", nullable = false)
    private float humidity;

    @Column(name = "pressure")
    private float pressure;
}
