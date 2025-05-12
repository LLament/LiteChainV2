#include "Blockchain.h"
#include "Transaction.h"
#include <iostream>

int main() {
    Blockchain myBlockchain;

    // 添加交易并挖矿
    myBlockchain.addTransaction(Transaction("Alice", "Bob", 50.0));
    myBlockchain.mineBlock();

    myBlockchain.addTransaction(Transaction("Bob", "Charlie", 30.0));
    myBlockchain.mineBlock();

    // 保存区块链到文件
    myBlockchain.saveToFile("blockchain.dat");

    // 创建新区块链实例并从文件加载
    Blockchain loadedBlockchain;
    loadedBlockchain.loadFromFile("blockchain.dat");

    // 验证加载的区块链
    if (loadedBlockchain.isChainValid()) {
        std::cout << "Loaded blockchain is valid.\n";
    }
    else {
        std::cout << "Loaded blockchain is NOT valid.\n";
    }

    return 0;
}