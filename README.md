<div id="top"></div>
<br />
<div align="center">
  <h3 align="center">Weather Station</h3>

  <p align="center">
    A project made during the "M242 — Mikroprozessoranwendung realisieren" class.
    <br />
    <br />
    <a href="https://weatherstation.just2flex.com">View Demo</a>
    ·
    <a href="ASSESSMENT_CRITERIA.md">See assessment criterias (german)</a>
    ·
    <a href="REFLECTION.md">Read reflection</a>
  </p>
</div>

<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#installation">Installation</a></li>
      </ul>
    </li>
    <li><a href="#roadmap">Roadmap</a></li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
    <li><a href="#resources">Resources</a></li>
  </ol>
</details>

## About The Project

"Weather station" is a temperature and humidity tracker powered by the "mBed DISCO_L475VG_IOT01A" mcu (our client). We utilize the embedded Wi-Fi module to communicate to send an update for the temperature and humidity every 30 seconds. The data is then visualized as a graph, accessible via the web ui.

### Built With

- [MCU Board](https://os.mbed.com/platforms/ST-Discovery-L475E-IOT01A/)
- [Java Spring](https://spring.io/)
- [Maria DB](https://mariadb.org/)
- [Chart.js](https://www.chartjs.org/)

<p align="right">(<a href="#top">back to top</a>)</p>

## Getting Started

### Prerequisites

- MariaDB server
- Docker installed

### Installation

<!-- TODO -->

<p align="right">(<a href="#top">back to top</a>)</p>

## Roadmap

- [x] Add ioTkit code
- [x] Create REST api
- [x] Add a UI
- [ ] Add SSL support
- [ ] Use the MQTT protocol

<p align="right">(<a href="#top">back to top</a>)</p>

## License

Copyright 2022 Dillan & Max

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at ttp://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

<p align="right">(<a href="#top">back to top</a>)</p>

## Contact

Dillan - d@illan.ch  
Max - max.gordon@edu.tbz.ch

<p align="right">(<a href="#top">back to top</a>)</p>

## Resources

- [iotkitv3/http](https://github.com/iotkitv3/http)
- [Google pki](https://pki.goog/repository/)

<p align="right">(<a href="#top">back to top</a>)</p>
