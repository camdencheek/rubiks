#include "rubik.h"
#include <pqxx/pqxx>
#include <boost/format.hpp>

using namespace std;
using namespace boost;

void insert_rep_lengths(int seq_length, pqxx::work &txn, sequence s, int orig_seq_length, Rubik &r) {
    if (seq_length != 0) {
        sequence temp = s;
        for (int i = 0; i < 6; i++) {
            temp.push_back(turn(i,true));
            insert_rep_lengths(seq_length - 1, txn, temp, orig_seq_length,r);
            temp.pop_back();

            temp.push_back(turn(i,false));
            insert_rep_lengths(seq_length - 1, txn, temp, orig_seq_length, r);
            temp.pop_back();
        }
    } else {
        int rep_length = r.run_sequence(s);

        boost::format conn_str("insert into recurrance(seq_length, sequence, rep_length) values (%1%, '%2%', %3%)");

        conn_str = conn_str % orig_seq_length % s.to_str() % rep_length;

        cout << conn_str.str() << endl;
        txn.exec(conn_str.str());

    }
}

int main() {

    Rubik r = Rubik();
    pqxx::connection c("dbname=rubik user=postgres");
    pqxx::work txn(c);


    sequence s;
    int sequence_length = 5;
    insert_rep_lengths(sequence_length,txn,s,sequence_length,r);
//    txn.commit();

    return 0;
}