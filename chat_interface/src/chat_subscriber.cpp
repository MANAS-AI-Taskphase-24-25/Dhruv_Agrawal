#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

class ChatSubscriber : public rclcpp::Node {
public:
    ChatSubscriber() : Node("chat_subscriber") {
        subscription_ = this->create_subscription<std_msgs::msg::String>(
            "chat_topic", 10,
            [this](const std_msgs::msg::String::SharedPtr msg) {
                RCLCPP_INFO(this->get_logger(), "Bob received: '%s'", msg->data.c_str());
            });
    }

private:
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscription_;
};

int main(int argc, char **argv) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<ChatSubscriber>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
