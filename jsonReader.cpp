#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h> // or jsoncpp/json.h , or json/json.h etc.
#include<jsoncpp/json/writer.h>
#include<string>

using namespace std;

int main() {
    ifstream ifs("population.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    //cout << "0" << obj["0"]["puzzle"] << endl;
    Json::FastWriter fastWriter;

    std::string output;
    for (int i = 0; i < 4; i++){
        output = fastWriter.write(obj[to_string(i)]["puzzle"]);
        cout << to_string(i) << output;
        cout << endl;
    }

    Json::Value population;
    population["0"]["puzzle"] = obj["0"]["puzzle"];
    population["0"]["length"] = obj["0"]["length"];
    population["0"]["width"] = obj["0"]["width"];
    population["0"]["pieces"] = obj["0"]["pieces"];

    std::ofstream file_id;
    file_id.open("outJsonfromcpp.json");
    Json::StyledWriter styledWriter;
    file_id << styledWriter.write(population);
    file_id.close();

}

