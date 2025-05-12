#pragma once
#include "Block.h"
#include "Transaction.h"
#include <vector>
#include <string>

class Blockchain {
private:
    std::vector<Block> chain;                 // ������
    std::vector<Transaction> transactionPool; // ��ǰ���׳�

public:
    Blockchain(); // ���캯��

    // ��ӽ��׵����׳�
    void addTransaction(const Transaction& tx);

    // �ڿ����������飩
    void mineBlock();

    // ��֤�������Ƿ���Ч
    bool isChainValid() const;

    // ��ȡ�������н���
    std::vector<Transaction> getAllTransactions() const;

    // ��ӡ������
    void printChain() const;

    // �������������ļ�
    void saveToFile(const std::string& filename) const;

    // ���ļ�����������
    void loadFromFile(const std::string& filename);
};