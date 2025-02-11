#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include <iostream>

class ChatPublisher : public rclcpp::Node {
public:
    ChatPublisher() : Node("chat_publisher") {
        publisher_ = this->create_publisher<std_msgs::msg::String>("chat_topic", 10);
        input_thread_ = std::thread(&ChatPublisher::publishMessages, this);
    }

    ~ChatPublisher() {
        input_thread_.join();
    }

private:
    void publishMessages() {
        while (rclcpp::ok()) {
            std::string message;
            std::cout << "You: ";
            std::getline(std::cin, message);
            auto msg = std_msgs::msg::String();
            msg.data = message;
            publisher_->publish(msg);
        }
    }

    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    std::thread input_thread_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ChatPublisher>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
