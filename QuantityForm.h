#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;

public ref class QuantityForm : public Form
{
public:
    NumericUpDown^ numericQuantity;
    Button^ btnOk;
    Button^ btnCancel;

    QuantityForm(String^ productName)
    {
        this->Text = "Modify Quantity - " + productName;
        this->Width = 300;
        this->Height = 180;
        this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
        this->StartPosition = FormStartPosition::CenterScreen;

        Label^ lbl = gcnew Label();
        lbl->Text = "Enter new quantity:";
        lbl->Location = Point(30, 20);
        lbl->Width = 200;
        this->Controls->Add(lbl);

        numericQuantity = gcnew NumericUpDown();
        numericQuantity->Location = Point(30, 50);
        numericQuantity->Width = 200;
        numericQuantity->Minimum = 1;
        numericQuantity->Maximum = 10000;
        numericQuantity->Value = 1;
        numericQuantity->DecimalPlaces = 0;
        this->Controls->Add(numericQuantity);

        btnOk = gcnew Button();
        btnOk->Text = "OK";
        btnOk->Location = Point(30, 90);
        btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
        this->Controls->Add(btnOk);

        btnCancel = gcnew Button();
        btnCancel->Text = "Cancel";
        btnCancel->Location = Point(160, 90);
        btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
        this->Controls->Add(btnCancel);
    }
};
