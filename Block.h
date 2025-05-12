#pragma once
#include "Transaction.h"
#include <vector>
#include <string>

class Block {
private:
    int index;
    std::vector<Transaction> transactions;
    std::string previousHash;
    std::string hash;
    long long timestamp;

public:
    Block(); // 默认构造函数
    Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash);

    // 获取区块的哈希
    std::string getHash() const;

    // 获取前一个区块的哈希
    std::string getPreviousHash() const;

    // 获取区块索引
    int getIndex() const;

    // 获取区块中的交易
    const std::vector<Transaction>& getTransactions() const;

    // 打印区块信息
    void printBlock() const;

    // 挖矿（模拟工作量证明）
    void mineBlock(int difficulty);

    // 序列化区块数据到文件
    void serialize(std::ofstream& out) const;

    // 从文件反序列化区块数据
    void deserialize(std::ifstream& in);
};