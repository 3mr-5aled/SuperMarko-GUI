
#pragma once

using namespace System;


const int numOfCustomers = 100;
const int numOfCategories = 10;
const int numOfProducts = 100;
ref struct CUSTOMER {
    int ID;
    String^ Name;
    String^ PhoneNumber;
    String^ Location;
    String^ Password;
};

ref struct PRODUCT {
    String^ Code;
    String^ Name;
    String^ Category;
    String^ ProductionDate;
    String^ ExpiredDate;
    double Price;
    double BasePrice;
};
ref struct ORDER {
    int CustomerID;
    array<PRODUCT^>^ Products = gcnew array<PRODUCT^>(numOfProducts);
    array<double>^ Amount = gcnew array<double>(numOfProducts);
    double TotalPrice = 0.0;
    int productcount = 0;
};
