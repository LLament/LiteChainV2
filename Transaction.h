#pragma once
#include <string>
#include <fstream>

class Transaction {
private:
    std::string sender;
    std::string receiver;
    double amount;

public:
    // 默认构造函数
    Transaction();

    // 带参数的构造函数
    Transaction(const std::string& sender, const std::string& receiver, double amount);

    // 序列化交易数据到文件
    void serialize(std::ofstream& out) const;

    // 从文件反序列化交易数据
    void deserialize(std::ifstream& in);

    // 打印交易信息
    void printTransaction() const;
};