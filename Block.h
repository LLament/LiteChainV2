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
    Block(); // Ĭ�Ϲ��캯��
    Block(int idx, const std::vector<Transaction>& txs, const std::string& prevHash);

    // ��ȡ����Ĺ�ϣ
    std::string getHash() const;

    // ��ȡǰһ������Ĺ�ϣ
    std::string getPreviousHash() const;

    // ��ȡ��������
    int getIndex() const;

    // ��ȡ�����еĽ���
    const std::vector<Transaction>& getTransactions() const;

    // ��ӡ������Ϣ
    void printBlock() const;

    // �ڿ�ģ�⹤����֤����
    void mineBlock(int difficulty);

    // ���л��������ݵ��ļ�
    void serialize(std::ofstream& out) const;

    // ���ļ������л���������
    void deserialize(std::ifstream& in);
};