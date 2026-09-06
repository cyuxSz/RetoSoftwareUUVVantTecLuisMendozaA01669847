// Luis Eduardo Mendoza Menendez A01669847
// Se suscribe al topic del sensor de agua, decide si hay una fuga, y publica el resultado en un topic nuevo para el resto del sistema.

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/bool.hpp"
#include "std_msgs/msg/string.hpp"

using std_msgs::msg::Bool;
using std_msgs::msg::String;

class WaterLeakDetector : public rclcpp::Node {
public:
    WaterLeakDetector() : Node("water_leak_detector") {
        // publicara el estado final en el topic "leak_status".
        publicador_estado_ = this->create_publisher<String>("leak_status", 10);

        // se suscribe al topic "water_sensor".
        // La funcion callback evaluar_lectura se ejecuta automaticamente, cada vez que llega un mensaje nuevo por ese topic.

        suscripcion_sensor_ = this->create_subscription<Bool>(
            "water_sensor", 10,
            std::bind(&WaterLeakDetector::evaluar_lectura, this, std::placeholders::_1));

        // std::placeholders::_1 le dice a std::bind  que el primer argumento que reciba evaluar_lectura se llenara automaticamente, cuando de verdad llegue un mensaje.

        RCLCPP_INFO(this->get_logger(), "Nodo water_leak_detector listo, esperando ");
    }

private:
    // Esta funcion se ejecuta cada vez que llega un mensaje nuevo por "water_sensor".
    // "const Bool::SharedPtr lectura" es el mensaje recibido:
    void evaluar_lectura(const Bool::SharedPtr lectura) {
        auto mensaje_salida = String();

        // si el sensor reporta "true", hay fuga.
        if (lectura->data) {
            mensaje_salida.data = "LEAK";
            RCLCPP_WARN(this->get_logger(), "Fuga detectada");
        } else {
            mensaje_salida.data = "OK";
            RCLCPP_INFO(this->get_logger(), "Sin fuga");
        }
        // RCLCPP_WARN marca el mensaje como advertencia para resaltar el caso importante.

        publicador_estado_->publish(mensaje_salida);
    }

    rclcpp::Publisher<String>::SharedPtr publicador_estado_;
    rclcpp::Subscription<Bool>::SharedPtr suscripcion_sensor_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WaterLeakDetector>());
    rclcpp::shutdown();
    return 0;
}



