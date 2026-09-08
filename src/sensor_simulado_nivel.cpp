// Luis Eduardo Mendoza Menendez A01669847
// Simula un sensor de agua publicando un valor booleano cada 2 segundos, alternando entre "sin fuga" y "con fuga".

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"

using namespace std::chrono_literals; // permite escribir "2s" en vez de rclcpp::Duration(2s)
using std_msgs::msg::Bool; //para escribir unicamente bool en lugar de std_msgs::msg::(bool o string) mas compacto de leer

// Un nodo en rclcpp se define como una clase que hereda de rclcpp::Node.
class SensorSimulado : public rclcpp::Node {
public:
    SensorSimulado() : Node("sensor_simulado") {
        publicador_ = this->create_publisher<Bool>("water_sensor", 10); // crea un publicador de mensajes booleanos en el topico "water_sensor"

        // create_wall_timer(intervalo, funcion_callback) ejecuta funcion_callback cada "intervalo" de tiempo, de forma repetida, mientras el nodo este vivo.
        // std::bind() conecta el temporizador con el metodo publicar_lectura() de esta misma clase.
        temporizador_ = this->create_wall_timer(
            2s, std::bind(&SensorSimulado::publicar_lectura, this));
    }

private:
    void publicar_lectura() {
        auto mensaje = Bool();

        // Alterna entre falso y verdadero en cada llamada, para simular que a veces hay fuga y a veces no.
        // hay_fuga_ es una variable de instancia que recuerda su valor entre llamadas.
        hay_fuga_ = !hay_fuga_;
        mensaje.data = hay_fuga_;
        publicador_->publish(mensaje);

        // RCLCPP_INFO es la forma estandar de imprimir un mensaje de registro en ROS 2, en vez de usar std::cout
        //  this->get_logger() asocia el mensaje con el nombre de este nodo en la salida de consola.
        RCLCPP_INFO(this->get_logger(), "%s",
                    mensaje.data ? "Agua detectada" : "Sin agua");
    }

    rclcpp::Publisher<Bool>::SharedPtr publicador_;
    rclcpp::TimerBase::SharedPtr temporizador_;
    bool hay_fuga_ = false;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);              // inicializa ROS 2
    rclcpp::spin(std::make_shared<SensorSimulado>());
    // rclcpp::spin(nodo) mantiene el nodo "vivo" y escuchando eventos
    // (en este caso,  el temporizador) hasta que se interrumpa manualmente (Ctrl+C).
    rclcpp::shutdown();
    return 0;
}
