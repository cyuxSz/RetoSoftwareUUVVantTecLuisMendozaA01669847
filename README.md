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

## Ejecutar

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
