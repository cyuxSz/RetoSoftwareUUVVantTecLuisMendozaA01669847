# RetoSoftwareUUVVantTecLuisMendozaA01669847
Paquete de ROS 2 en C++ que detecta fugas de agua a partir de un sensor simulado, como parte del reto de reclutamiento de VantTec UUV.

Autor: Luis Eduardo Mendoza Menendez A01669847

## Nodos
- **sensor_simulado**: publica una lectura booleana en `/water_sensor`
  cada 2 segundos, alternando entre falso/verdadero.
- **water_leak_detector_node**: se suscribe a `/water_sensor`, evalúa
  si hay fuga, y publica el estatus en `/leak_status`.

## Requisitos

- ROS 2 Humble
- Ubuntu 22.04

## Compilar

Clona este repositorio dentro de la carpeta `src` de tu workspace de ROS 2
(por ejemplo, si tu workspace se llama `ros2_ws` (como el mio), quedaría en
`~/ros2_ws/src/water_leak_detector`).

Luego, ubícate en la raíz de tu workspace (un nivel arriba de `src`) y compila:

```bash
cd ~/ros2_ws   # reemplaza esto por la ruta de tu workspace
colcon build --packages-select water_leak_detector
source install/setup.bash
```

## Ejecutar fase 2

Desde cualquier terminal donde ya hayas hecho previamente `source install/setup.bash`:

Terminal 1:
```bash
ros2 run water_leak_detector sensor_simulado
```

Terminal 2:
```bash
ros2 run water_leak_detector water_leak_detector_node
```

## Fase 3 (Pruebas realizadas) 

Primeramente como se solicitó hacer pruebas de mediciones de cuando no hay agua, si hay, valores cercanos al limite, se migró el sensor de un valor booleano a un nivel continuo (`std_msgs/Float32`,
rango 0.0-1.0) con un umbral de 0.5, ya que estas mediciones no pueden ser realizadas con un `true`/`false`. 

En este caso los nuevos nodos funcionan de la siguiente manera: 
- **sensor_simulado_nivel**: publica un nivel de agua (`Float32`, 0.0-1.0)
  con ruido en `/water_level`.
- **water_leak_detector_node_nivel**: se suscribe a `/water_level`, compara
  contra un umbral de 0.5, y publica el estatus en `/leak_status_nivel`.

Los nodos originales (`sensor_simulado`, `water_leak_detector_node`, con
`Bool`) se conservan sin cambios de la Fase 2.

**Prueba 1 Sin agua:** se publicó manualmente un nivel de 0.1 en
`/water_sensor_nivel`. El nodo respondió correctamente con "Sin fuga".

**Prueba 2 Con agua:** se publicó un nivel de 0.9. El nodo respondió
correctamente con "Hay fuga".

**Prueba 3 Valores cercanos al límite:** se probaron los valores 0.49
(justo debajo del umbral) y 0.51 (justo arriba). El primero dio "Sin fuga" y
el segundo "Hay fuga", confirmando que la comparación funciona exactamente
donde se espera, sin margen de error de ningún lado.

**Prueba 4 Mediciones con ruido:** se dejó corriendo el nodo
`sensor_simulado_nivel`, que agrega ruido aleatorio (± 0.05) a cada lectura.
Se observó que el nivel nunca llega a ser exactamente 0.15 o 0.85, sino que
varía un poco en cada publicación, y aun así el detector clasificó
correctamente en todos los casos observados, ya que el ruido nunca fue
suficiente para cruzar el umbral de 0.5 por accidente.

## Ejecutar fase 3

Desde cualquier terminal donde ya hayas hecho previamente `source install/setup.bash`:

Terminal 1:
```bash
ros2 run water_leak_detector sensor_simulado_nivel
```

Terminal 2:
```bash
ros2 run water_leak_detector water_leak_detector_node_nivel
```

## Referencias

Open Robotics. (s. f.-a). *Creating a workspace*. ROS 2 Documentation.
https://docs.ros.org/en/jazzy/Tutorials/Beginner-Client-Libraries/Creating-A-Workspace/Creating-A-Workspace.html

Open Robotics. (s. f.-b). *std_msgs*. ROS 2 Documentation.
https://docs.ros.org/en/jazzy/p/std_msgs

Open Robotics. (s. f.-c). *Understanding nodes*. ROS 2 Documentation.
https://docs.ros.org/en/jazzy/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Nodes/Understanding-ROS2-Nodes.html

Open Robotics. (s. f.-d). *Understanding topics*. ROS 2 Documentation.
https://docs.ros.org/en/jazzy/Tutorials/Beginner-CLI-Tools/Understanding-ROS2-Topics/Understanding-ROS2-Topics.html

Open Robotics. (s. f.-e). *Writing a simple publisher and subscriber (C++)* . ROS 2 Documentation.
https://docs.ros.org/en/jazzy/Tutorials/Be 65
ginner-Client-Libraries/Writing-A-Simple-Cpp-Publisher-And-Subscriber.html
