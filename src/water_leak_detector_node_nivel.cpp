// Luis Eduardo Mendoza Menendez A01669847
// Copia de water_leak_detector_node.cpp para la fase 3: se suscribe
// al nivel de agua en vez de un booleano, y compara contra un umbral fijo para decidir si hay fuga.

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include "std_msgs/msg/string.hpp"

using std_msgs::msg::String;
using std_msgs::msg::Float32;

class WaterLeakDetectorNivel : public rclcpp::Node {
public:
    WaterLeakDetectorNivel() : Node("water_leak_detector_nivel") {
        publicador_estado_ = this->create_publisher<String>("leak_status_nivel", 10);

        suscripcion_sensor_ = this->create_subscription<Float32>(
            "water_level", 10,
            std::bind(&WaterLeakDetectorNivel::evaluar_lectura, this, std::placeholders::_1));

        RCLCPP_INFO(this->get_logger(), "Nodo water_leak_detector_nivel listo, esperando lecturas");
    }

private:
    void evaluar_lectura(const Float32::SharedPtr lectura) {
        auto mensaje_salida = String();

        if (lectura->data >= UMBRAL_FUGA) {
            mensaje_salida.data = "Fuga";
            RCLCPP_WARN(this->get_logger(), "Nivel del agua:  %.3f. Hay fuga",
                        lectura->data);
        } else {
            mensaje_salida.data = "Sin fuga";
            RCLCPP_INFO(this->get_logger(), "Nivel del agua:  %.3f. Sin fuga",
                        lectura->data);
        }

        publicador_estado_->publish(mensaje_salida);
    }

    // Se usa "static constexpr" por eficiencia:
    // static: La constante pertenece a la clase, no a cada instancia individual.
    // constexpr: Se evalua en tiempo de compilacion. A diferencia de const,
    // esto nos permite inicializar valores float o double directamente dentro
    // de la clase sin tener que definirlos externamente en este archivo.
    static constexpr float UMBRAL_FUGA = 0.5f;

    rclcpp::Publisher<String>::SharedPtr publicador_estado_;
    rclcpp::Subscription<Float32>::SharedPtr suscripcion_sensor_;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<WaterLeakDetectorNivel>());
    rclcpp::shutdown();
    return 0;
}












