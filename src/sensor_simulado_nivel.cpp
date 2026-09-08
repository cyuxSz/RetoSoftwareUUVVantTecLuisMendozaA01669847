// Luis Eduardo Mendoza Menendez A01669847
// Copia de sensor_simulado.cpp  en vez de un booleano, publica un nivel de agua (0.0 a 1.0) con ruido, para poder probar escenarios
// de valores cercanos al limite y ruido, que no tienen sentido con un simple true/false.

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"
#include <random>

using namespace std::chrono_literals;
using std_msgs::msg::Float32;

class SensorSimuladoNivel : public rclcpp::Node {
public:
    SensorSimuladoNivel()
        : Node("sensor_simulado_nivel"),
          generador_(std::random_device{}()),   // para generar la aleatoridad
          ruido_(-0.05f, 0.05f) {                // distribucion uniforme entre -0.05 y +0.05

        publicador_ = this->create_publisher<Float32>("water_level", 10);

        temporizador_ = this->create_wall_timer(
            2s, std::bind(&SensorSimuladoNivel::publicar_lectura, this));
    }

private:
    void publicar_lectura() {
        contador_++;

        // Cada 5 lecturas simula una fuga, el resto del tiempo sin fuga. modulo da el residuo de la
        // division; "contador_ % 5 == 0" es verdadero una vez de cada 5 vueltas.
        float nivel_base = (contador_ % 5 == 0) ? 0.85f : 0.15f;

        // ruido_(generador_) saca un numero aleatorio nuevo cada vez, dentro
        // del rango que se configuro (-0.05 a +0.05), simulando la imprecision normal de un sensor.
        float nivel_con_ruido = nivel_base + ruido_(generador_);

        auto mensaje = Float32();
        mensaje.data = nivel_con_ruido;
        publicador_->publish(mensaje);

        RCLCPP_INFO(this->get_logger(), "%.3f", nivel_con_ruido);
    }

    rclcpp::Publisher<Float32>::SharedPtr publicador_;
    rclcpp::TimerBase::SharedPtr temporizador_;

    // Motor generador de numeros aleatorios  y la distribucion que define el rango.
    std::mt19937 generador_;
    std::uniform_real_distribution<float> ruido_;

    int contador_ = 0;
};

int main(int argc, char *argv[]) {
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SensorSimuladoNivel>());
    rclcpp::shutdown();
    return 0;
}
