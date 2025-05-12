#include "Transaction.h"
#include <iostream>

// 默认构造函数
Transaction::Transaction() : sender(""), receiver(""), amount(0.0) {}

// 带参数的构造函数
Transaction::Transaction(const std::string& sender, const std::string& receiver, double amount)
    : sender(sender), receiver(receiver), amount(amount) {}

// 序列化交易数据到文件
void Transaction::serialize(std::ofstream& out) const {
    size_t senderLen = sender.size();
    out.write(reinterpret_cast<const char*>(&senderLen), sizeof(senderLen));
    out.write(sender.data(), senderLen);

    size_t receiverLen = receiver.size();
    out.write(reinterpret_cast<const char*>(&receiverLen), sizeof(receiverLen));
    out.write(receiver.data(), receiverLen);

    out.write(reinterpret_cast<const char*>(&amount), sizeof(amount));
}

// 从文件反序列化交易数据
void Transaction::deserialize(std::ifstream& in) {
    size_t senderLen;
    in.read(reinterpret_cast<char*>(&senderLen), sizeof(senderLen));
    sender.resize(senderLen);
    in.read(&sender[0], senderLen);

    size_t receiverLen;
    in.read(reinterpret_cast<char*>(&receiverLen), sizeof(receiverLen));
    receiver.resize(receiverLen);
    in.read(&receiver[0], receiverLen);

    in.read(reinterpret_cast<char*>(&amount), sizeof(amount));
}

// 打印交易信息
void Transaction::printTransaction() const {
    std::cout << "Sender: " << sender << ", Receiver: " << receiver << ", Amount: " << amount << "\n";
}