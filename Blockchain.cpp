#include "Blockchain.h"
#include <iostream>
#include <fstream>

// 构造函数
Blockchain::Blockchain() {
    // 初始化创世区块
    chain.emplace_back(0, std::vector<Transaction>(), "0");
}

// 添加交易到交易池
void Blockchain::addTransaction(const Transaction& tx) {
    transactionPool.push_back(tx);
}

// 挖矿（生成新区块）
void Blockchain::mineBlock() {
    if (transactionPool.empty()) {
        std::cout << "No transactions to mine.\n";
        return;
    }
    // 获取前一个区块的哈希
    const std::string& previousHash = chain.back().getHash();
    // 创建新区块
    Block newBlock(chain.size(), transactionPool, previousHash);
    newBlock.mineBlock(2); // 挖矿难度设为 2
    chain.push_back(newBlock);
    // 清空交易池
    transactionPool.clear();
    std::cout << "Block mined successfully!\n";
}

// 验证区块链是否有效
bool Blockchain::isChainValid() const {
    for (size_t i = 1; i < chain.size(); ++i) {
        const Block& currentBlock = chain[i];
        const Block& previousBlock = chain[i - 1];

        // 验证当前区块的哈希是否正确
        if (currentBlock.getHash() != std::to_string(currentBlock.getIndex()) + currentBlock.getPreviousHash()) {
            std::cout << "Block " << currentBlock.getIndex() << " has invalid hash.\n";
            return false;
        }

        // 验证当前区块的 previousHash 是否匹配前一个区块的哈希
        if (currentBlock.getPreviousHash() != previousBlock.getHash()) {
            std::cout << "Block " << currentBlock.getIndex() << " has invalid previous hash.\n";
            return false;
        }
    }
    return true;
}

// 获取链上所有交易
std::vector<Transaction> Blockchain::getAllTransactions() const {
    std::vector<Transaction> allTransactions;

    // 遍历所有区块
    for (const auto& block : chain) {
        const auto& transactions = block.getTransactions(); // 假设 Block 类有 getTransactions 方法
        allTransactions.insert(allTransactions.end(), transactions.begin(), transactions.end());
    }

    return allTransactions;
}

// 打印区块链
void Blockchain::printChain() const {
    for (const auto& block : chain) {
        block.printBlock();
    }
}

// 保存区块链到文件
void Blockchain::saveToFile(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file for saving: " << filename << "\n";
        return;
    }

    size_t chainSize = chain.size();
    outFile.write(reinterpret_cast<const char*>(&chainSize), sizeof(chainSize));

    for (const auto& block : chain) {
        block.serialize(outFile);
    }

    outFile.close();
    std::cout << "Blockchain saved to " << filename << " successfully.\n";
}

// 从文件加载区块链
void Blockchain::loadFromFile(const std::string& filename) {
    std::ifstream inFile(filename, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open file for loading: " << filename << "\n";
        return;
    }

    chain.clear();

    size_t chainSize;
    inFile.read(reinterpret_cast<char*>(&chainSize), sizeof(chainSize));

    for (size_t i = 0; i < chainSize; ++i) {
        Block block;
        block.deserialize(inFile);
        chain.push_back(block);
    }

    inFile.close();
    std::cout << "Blockchain loaded from " << filename << " successfully.\n";
}