# RetoSoftwareUUVVantTecLuisMendozaA01669847
Paquete de ROS 2 en C++ que detecta fugas de agua a partir de un sensor simulado, como parte del reto de reclutamiento de VantTec UUV.

Autor: Luis Eduardo Mendoza Menendez A01669847

## Nodos
- **sensor_simulado**: publica una lectura booleana en `/water_sensor`
  cada 2 segundos, alternando entre falso/verdadero.
- **water_leak_detector_node**: se suscribe a `/water_sensor`, evalúa
  si hay fuga, y publica "OK" o "LEAK" en `/leak_status`.
