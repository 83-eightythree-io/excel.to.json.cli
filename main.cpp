#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include "rapidjson/document.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include <libxml/tree.h>
#include <xlsxio_read.h>

using namespace std;
using namespace rapidjson;

int main(int argc, char **argv) {
    string filepath;
    xlsxioreader reader;

    cout << "Welcome to Excel to Json parser!" << endl;
    cout << "Enter the file (absolute path) you wish to parse: ";
    cin >> filepath;
    cout << "Parsing file...";

    // instantiates the json object
    Document output;
    output.SetArray();

    // open the XLSX file
    if ((reader = xlsxioread_open(filepath.c_str())) == nullptr) {
        cout << "Error opening excel file" << endl;
        return 1;
    }

    vector<string> headers{};
    char* value;
    xlsxioreadersheet sheet;
    const char* sheet_name = nullptr;
    int row_counter = 0, column_counter = 0;
    if ((sheet = xlsxioread_sheet_open(reader, sheet_name, XLSXIOREAD_SKIP_EMPTY_ROWS)) != nullptr) {
        while (xlsxioread_sheet_next_row(sheet)) {
            column_counter = 0;
            Value o;
            o.SetObject();

            while ((value = xlsxioread_sheet_next_cell(sheet)) != nullptr) {
                // if headers
                if (row_counter == 0) {
                    headers.emplace_back(value);
                } else {
                    Value key(headers.at(column_counter).c_str(), output.GetAllocator());
                    Value v(value, output.GetAllocator());
                    o.AddMember(key, v, output.GetAllocator());
                }

                xlsxioread_free(value);
                column_counter++;
            }

            if (row_counter != 0) {
                output.PushBack(o, output.GetAllocator());
            }

            row_counter++;
        }
        xlsxioread_sheet_close(sheet);
    }

    xlsxioread_close(reader);

    FILE* f = fopen("/Users/joao.lopes/CLionProjects/course/output.json", "wb");
    char writeBuffer[65536];
    FileWriteStream os(f, writeBuffer,sizeof(writeBuffer));
    Writer<FileWriteStream> writer(os);
    output.Accept(writer);
    fclose(f);

//    for (const auto & header : headers) {
//        cout << header << endl;
//    }

    return 0;
}

// /Users/joao.lopes/Downloads/Extract_Automotive_Luxembourg_202306.xlsx
