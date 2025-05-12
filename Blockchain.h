#pragma once
#include "Block.h"
#include "Transaction.h"
#include <vector>
#include <string>

class Blockchain {
private:
    std::vector<Block> chain;                 // 区块链
    std::vector<Transaction> transactionPool; // 当前交易池

public:
    Blockchain(); // 构造函数

    // 添加交易到交易池
    void addTransaction(const Transaction& tx);

    // 挖矿（生成新区块）
    void mineBlock();

    // 验证区块链是否有效
    bool isChainValid() const;

    // 获取链上所有交易
    std::vector<Transaction> getAllTransactions() const;

    // 打印区块链
    void printChain() const;

    // 保存区块链到文件
    void saveToFile(const std::string& filename) const;

    // 从文件加载区块链
    void loadFromFile(const std::string& filename);
};