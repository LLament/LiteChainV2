#include "Block.h"
#include <iostream>
#include <fstream>

// 默认构造函数
Block::Block() : index(0), previousHash(""), hash(""), timestamp(0) {}

// 带参数的构造函数
Block::Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash)
    : index(idx), transactions(txs), previousHash(prevHash), hash(""), timestamp(0) {}

// 获取当前区块的哈希
std::string Block::getHash() const {
    return hash;
}

// 获取前一个区块的哈希
std::string Block::getPreviousHash() const {
    return previousHash;
}

// 获取区块索引
int Block::getIndex() const {
    return index;
}

// 获取区块中的交易
const std::vector<Transaction>& Block::getTransactions() const {
    return transactions;
}

// 打印区块信息
void Block::printBlock() const {
    std::cout << "Block Index: " << index << "\n";
    std::cout << "Previous Hash: " << previousHash << "\n";
    std::cout << "Hash: " << hash << "\n";
    for (const auto& tx : transactions) {
        tx.printTransaction();
    }
}

// 挖矿（模拟工作量证明）
void Block::mineBlock(int difficulty) {
    // 模拟挖矿逻辑
}

// 序列化区块数据到文件
void Block::serialize(std::ofstream& out) const {
    out.write(reinterpret_cast<const char*>(&index), sizeof(index));
    size_t txCount = transactions.size();
    out.write(reinterpret_cast<const char*>(&txCount), sizeof(txCount));
    for (const auto& tx : transactions) {
        tx.serialize(out);
    }
    size_t hashLen = hash.size();
    out.write(reinterpret_cast<const char*>(&hashLen), sizeof(hashLen));
    out.write(hash.data(), hashLen);

    size_t prevHashLen = previousHash.size();
    out.write(reinterpret_cast<const char*>(&prevHashLen), sizeof(prevHashLen));
    out.write(previousHash.data(), prevHashLen);

    out.write(reinterpret_cast<const char*>(&timestamp), sizeof(timestamp));
}

// 从文件反序列化区块数据
void Block::deserialize(std::ifstream& in) {
    in.read(reinterpret_cast<char*>(&index), sizeof(index));
    size_t txCount;
    in.read(reinterpret_cast<char*>(&txCount), sizeof(txCount));
    transactions.clear();
    for (size_t i = 0; i < txCount; ++i) {
        Transaction tx;
        tx.deserialize(in);
        transactions.push_back(tx);
    }
    size_t hashLen;
    in.read(reinterpret_cast<char*>(&hashLen), sizeof(hashLen));
    hash.resize(hashLen);
    in.read(&hash[0], hashLen);

    size_t prevHashLen;
    in.read(reinterpret_cast<char*>(&prevHashLen), sizeof(prevHashLen));
    previousHash.resize(prevHashLen);
    in.read(&previousHash[0], prevHashLen);

    in.read(reinterpret_cast<char*>(&timestamp), sizeof(timestamp));
}