#pragma once
#include "DataModels.h"
#include <string>


using namespace System;

namespace SuperMarkoGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Printing;
	using namespace IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	 

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
			Button^ selectedButton = nullptr;  // add this as a class member variable
		MyForm(void)
		{
			currentCustomerIndex = -1;
			// Initialize arrays
			customers = gcnew array<CUSTOMER^>(numOfCustomers);
			orders = gcnew array<ORDER^>(numOfCustomers);
			products = gcnew array<array<PRODUCT^>^>(numOfCategories);
			productCounts = gcnew array<int>(numOfCategories);

			for (int i = 0; i < numOfCategories; ++i) {
				products[i] = gcnew array<PRODUCT^>(numOfProducts);
				productCounts[i] = 0;
			}

			InitializeComponent();

			// Load by category into their dedicated panels
			loadCategory("Fruit", flowLayoutPanel3);           // Fruits
			loadCategory("Vegetables", flowLayoutPanel4);      // Vegetables
			loadCategory("Dairy&Eggs", flowLayoutPanel5);      // Dairy
			loadCategory("Meats", flowLayoutPanel6);           // Butcher shop
			loadCategory("Fish", flowLayoutPanel7);            // Seafood
			loadCategory("Poultry", flowLayoutPanel8);         // Poultry
			loadCategory("Bakery&Bread", flowLayoutPanel9);    // Bakery
			loadCategory("Snacks&Sweets", flowLayoutPanel10);  // Snacks
			loadCategory("Household&Cleaning_Supplies", flowLayoutPanel11); // Household
			loadCategory("Pet_Supplies", flowLayoutPanel12);   // Pet supplies

			//
			//TODO: Add the constructor code here
			//
		}


		

		void refreshOrderList() {
			orderList->Controls->Clear();

			for (int i = 0; i < orders[currentCustomerIndex]->productcount; i++) {
				if (orders[currentCustomerIndex]->Products[i] == nullptr) continue;

				Label^ lblName = gcnew Label();
				lblName->Text = "Product: " + orders[currentCustomerIndex]->Products[i]->Name;
				lblName->AutoSize = false;
				lblName->Width = 300;
				lblName->Height = 30;
				lblName->Location = Point(10, 10);

				Label^ lblQuantity = gcnew Label();
				lblQuantity->Text = "Quantity: " + (orders[currentCustomerIndex]->Amount[i] / orders[currentCustomerIndex]->Products[i]->Price).ToString();
				lblQuantity->AutoSize = false;
				lblQuantity->Width = 100;
				lblQuantity->Height = 30;
				lblQuantity->Location = Point(320, 10);

				Button^ btnDelete = gcnew Button();
				btnDelete->Text = "Delete";
				btnDelete->Width = 80;
				btnDelete->Height = 30;
				btnDelete->Location = Point(430, 10);
				// btnDelete->Click += ... your delete code here

				Button^ btnModify = gcnew Button();
				btnModify->Text = "Modify";
				btnModify->Width = 80;
				btnModify->Height = 30;
				btnModify->Location = Point(520, 10);
				btnModify->Click += gcnew EventHandler(this, &MyForm::handleModifyQuantityClick);

				orderList->Controls->Add(lblName);
				orderList->Controls->Add(lblQuantity);
				orderList->Controls->Add(btnDelete);
				orderList->Controls->Add(btnModify);

			}
		}
		void populateCurrentUserInfo(Object^ sender, EventArgs^ e) {
			if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr) {
				MessageBox::Show("User not logged in or data missing.");
				tb_currentPassword->UseSystemPasswordChar = false;
				tb_currentPassword->Text = "";  // Avoid accessing user->Password here
				return;
			}

			CUSTOMER^ user = customers[currentCustomerIndex];
			tb_currentUsername->Text = user->Name;
			tb_currentPhoneNumber->Text = user->PhoneNumber;
			tb_currentLocation->Text = user->Location;
			tb_currentPassword->UseSystemPasswordChar = true;
			tb_currentPassword->Text = user->Password;
			textBox8->Text = user->Password; // For reset password
			tb_edit_username->Text = user->Name;
			tb_edit_phonenumber->Text = user->PhoneNumber;
			tb_edit_location->Text = user->Location;
		}
		void hideAllMainPanels() {
			pn_orders->Visible = false;
			pn_products->Visible = false;
			pn_edit_information->Visible = false;
			pn_blank->Visible = false;
		}
		void showPanel(Panel^ panelToShow) {
			if (panelToShow == pn_login || panelToShow == pn_register || panelToShow == pn_start || panelToShow == pn_thankyou) {
				pn_defualt->Visible = false;
				pn_defualt->SendToBack();
			}
			else {
				pn_defualt->Visible = true;
			}
			hideAllMainPanels();
			panelToShow->Visible = true;
			panelToShow->BringToFront();
		}
		void showCategoryPanel(Panel^ panelToShow) {
			panelToShow->Visible = true;
			panelToShow->BringToFront();
		}
		void MenuBGColor(Button^ buttonToChange) {
			// Reset all buttons
			btn_edit_information->BackColor = Color::Transparent;
			btn_orders->BackColor = Color::Transparent;
			btn_products->BackColor = Color::Transparent;
			btn_TotalBill->BackColor = Color::Transparent;

			btn_edit_information->ForeColor = Color::White;
			btn_orders->ForeColor = Color::White;
			btn_products->ForeColor = Color::White;
			btn_TotalBill->ForeColor = Color::White;

			// Set the selected button
			selectedButton = buttonToChange;

			buttonToChange->BackColor = Color::FromArgb(230, 52, 98); // Red
			buttonToChange->ForeColor = Color::Black;
		}
		//Validations
		bool validateUsername(String^ username, Label^ lb_username_message) {
			// Clear any previous error message
			lb_username_message->Text = "";

			// Check if username is empty or contains only spaces
			if (String::IsNullOrEmpty(username) || username->Trim()->Length == 0) {
				lb_username_message->Text = "Username cannot be empty!";
				return false;
			}

			// Check if username length is between 3 and 20 characters
			if (username->Length < 3 || username->Length > 20) {
				lb_username_message->Text = "Username must be between 3 and 20 characters.";
				return false;
			}

			// Check if username contains only valid characters
			if (!System::Text::RegularExpressions::Regex::IsMatch(username, "^[a-zA-Z0-9._]+$")) {
				lb_username_message->Text = "Username can only contain letters, numbers, dots (.), and underscores (_).";
				return false;
			}

			// Check if username starts or ends with '.' or '_'
			if (username->StartsWith(".") || username->StartsWith("_") || username->EndsWith(".") || username->EndsWith("_")) {
				lb_username_message->Text = "Username cannot start or end with '.' or '_'.";
				return false;
			}

			// Check if username contains consecutive '.' or '_'
			if (username->Contains("..") || username->Contains("__")) {
				lb_username_message->Text = "Username cannot contain consecutive '.' or '_'.";
				return false;
			}

			// If all validations pass
			return true;
		}
		bool validatePassword(String^ password, Label^ lb_password_message) {
			// Clear any previous error message
			lb_password_message->Text = "";

			// Check if password is empty
			if (String::IsNullOrEmpty(password)) {
				lb_password_message->Text = "Password cannot be empty!";
				return false;
			}

			// Check if password contains spaces
			if (password->Contains(" ")) {
				lb_password_message->Text = "Password cannot contain spaces!";
				return false;
			}

			// Check if password is at least 8 characters long
			if (password->Length < 8) {
				lb_password_message->Text = "Password must be at least 8 characters long!";
				return false;
			}

			// Check if password contains at least one uppercase letter
			if (!System::Text::RegularExpressions::Regex::IsMatch(password, "[A-Z]")) {
				lb_password_message->Text = "Password must contain at least one uppercase letter!";
				return false;
			}

			// Check if password contains at least one lowercase letter
			if (!System::Text::RegularExpressions::Regex::IsMatch(password, "[a-z]")) {
				lb_password_message->Text = "Password must contain at least one lowercase letter!";
				return false;
			}

			// Check if password contains at least one numeric digit
			if (!System::Text::RegularExpressions::Regex::IsMatch(password, "[0-9]")) {
				lb_password_message->Text = "Password must contain at least one number!";
				return false;
			}

			// Check if password contains at least one special character
			if (!System::Text::RegularExpressions::Regex::IsMatch(password, "[!@#$%^&*()\\-_=+\\[\\]{}|;:'\",.<>?/\\\\]")) {
				lb_password_message->Text = "Password must contain at least one special character!";
				return false;
			}

			// If all validations pass
			return true;
		}
		bool validatePhoneNumber(String^ phoneNumber, Label^ lb_phonenumber_message) {
			// Clear any previous error message
			lb_phonenumber_message->Text = "";

			// Check if phone number is empty or contains spaces
			if (String::IsNullOrEmpty(phoneNumber) || phoneNumber->Contains(" ")) {
				lb_phonenumber_message->Text = "Phone number cannot be empty or contain spaces!";
				return false;
			}

			// Check if phone number is exactly 11 digits and contains only numbers
			if (phoneNumber->Length != 11 || !System::Text::RegularExpressions::Regex::IsMatch(phoneNumber, "^[0-9]+$")) {
				lb_phonenumber_message->Text = "Phone number must be 11 digits long and contain only numbers.";
				return false;
			}

			// Check if phone number starts with valid Egyptian prefixes
			if (!phoneNumber->StartsWith("010") && !phoneNumber->StartsWith("011") &&
				!phoneNumber->StartsWith("012") && !phoneNumber->StartsWith("015")) {
				lb_phonenumber_message->Text = "Invalid phone number prefix. Must start with 010, 011, 012, or 015.";
				return false;
			}

			// If all validations pass
			return true;
		}
		bool validateLocation(String^ location, Label^ lb_location_message) {
			// Clear any previous error message
			lb_location_message->Text = "";

			// Check if location is empty or contains only spaces
			if (String::IsNullOrEmpty(location) || location->Trim()->Length == 0) {
				lb_location_message->Text = "Location cannot be empty!";
				return false;
			}

			// Check if location is at least 5 characters long
			if (location->Length < 5) {
				lb_location_message->Text = "Location must be at least 5 characters long.";
				return false;
			}

			// Check if location does not exceed 100 characters
			if (location->Length > 100) {
				lb_location_message->Text = "Location cannot exceed 100 characters.";
				return false;
			}

			// Check if location contains only valid characters
			if (!System::Text::RegularExpressions::Regex::IsMatch(location, "^[a-zA-Z0-9 ,.-]+$")) {
				lb_location_message->Text = "Location contains invalid characters. Only letters, numbers, spaces, commas, periods, and hyphens are allowed.";
				return false;
			}

			// If all validations pass
			return true;
		}




		int getCategoryIndex(String^ categoryName) {
			if (categoryName == "Fruit") return 0;
			if (categoryName == "Vegetables") return 1;
			if (categoryName == "Dairy&Eggs") return 2;
			if (categoryName == "Meats") return 3;
			if (categoryName == "Fish") return 4;
			if (categoryName == "Poultry") return 5;
			if (categoryName == "Bakery&Bread") return 6;
			if (categoryName == "Snacks&Sweets") return 7;
			if (categoryName == "Household&Cleaning_Supplies") return 8;
			if (categoryName == "Pet_Supplies") return 9;
			return -1;
		}
		void handleBackToCategories(Object^ sender, EventArgs^ e) {
			pn_fruits_category->Visible = false;
			pn_vegetable_category->Visible = false;
			pn_dairy_category->Visible = false;
			pn_butchershop_category->Visible = false;
			pn_seafood_category->Visible = false;
			pn_poultry_category->Visible = false;
			pn_bakery_category->Visible = false;
			pn_snacks_category->Visible = false;
			pn_household_category->Visible = false;
			pn_pet_supplies_category->Visible = false;
			pn_main_category->Visible = true;
		}
		void loadCategory(String^ categoryFilter, FlowLayoutPanel^ panelToFill) {
			try {
				panelToFill->Controls->Clear();

				// === Create and add the black panel with "Back" button ===
				Button^ btnBack = gcnew Button();
				btnBack->Text = "Back";
				btnBack->Width = 150;
				btnBack->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F);
				btnBack->Height = 50;
				btnBack->BackColor = Color::FromArgb(230, 52, 98);
				btnBack->ForeColor = Color::White;
				btnBack->FlatStyle = FlatStyle::Flat;
				btnBack->Click += gcnew EventHandler(this, &MyForm::handleBackToCategories);

				Panel^ pn_back = gcnew Panel();
				pn_back->Width = 750;
				pn_back->Height = 50;
				pn_back->BackColor = Color::FromArgb(239, 239, 239);
				pn_back->Controls->Add(btnBack);

				panelToFill->Controls->Add(pn_back);

				// === Load products from file ===
				StreamReader^ reader = gcnew StreamReader("productmenu.txt");
				String^ line;

				while ((line = reader->ReadLine()) != nullptr) {
					array<String^>^ parts = line->Split(',');

					if (parts->Length < 7) continue;
					if (parts[3]->Trim()->ToLower() != categoryFilter->ToLower()) continue;

					String^ code = parts[1];
					String^ name = parts[2];
					String^ prodDate = parts[4];
					String^ expDate = parts[5];
					String^ price = parts[6];
					String^ categoryName = parts[3];

					int catIndex = getCategoryIndex(categoryName);
					if (catIndex == -1 || productCounts[catIndex] >= numOfProducts) continue;

					PRODUCT^ p = gcnew PRODUCT();
					p->Code = code;
					p->Name = name;
					p->Category = categoryName;
					p->Price = Convert::ToDouble(price);
					p->BasePrice = p->Price * 0.8;
					p->ProductionDate = prodDate;
					p->ExpiredDate = expDate;

					products[catIndex][productCounts[catIndex]++] = p;

					// === Create product panel ===
					Panel^ productPanel = gcnew Panel();
					productPanel->BackColor = Color::White;
					productPanel->Margin = System::Windows::Forms::Padding(10);
					productPanel->Width = 250;
					productPanel->AutoSize = true;
					productPanel->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;

					FlowLayoutPanel^ innerPanel = gcnew FlowLayoutPanel();
					innerPanel->FlowDirection = FlowDirection::TopDown;
					innerPanel->WrapContents = false;
					innerPanel->BackColor = Color::White;
					innerPanel->AutoSize = true;
					innerPanel->Dock = DockStyle::Fill;
					innerPanel->Padding = System::Windows::Forms::Padding(0, 0, 0, 10);

					PictureBox^ productImage = gcnew PictureBox();
					productImage->Size = Drawing::Size(230, 100);
					productImage->SizeMode = PictureBoxSizeMode::Zoom;

					String^ imageName = name->Replace(" ", "_")->Replace("(", "")->Replace(")", "")->Replace("\"", "") + ".jpg";
					String^ imagePath = "images\\" + imageName;

					try {
						productImage->Image = Image::FromFile(imagePath);
					}
					catch (...) {
						productImage->Image = Image::FromFile("images\\placeholder.jpg");
					}
					innerPanel->Controls->Add(productImage);

					array<String^>^ labels = {
						"Name: " + name,
						"Code: " + code,
						"Category: " + categoryName,
						"Production Date: " + prodDate,
						"Expiration Date: " + expDate,
						"Price: " + price + " EGP"
					};

					for each (String ^ text in labels) {
						Label^ lbl = gcnew Label();
						lbl->Text = text;
						lbl->AutoSize = false;
						lbl->Width = 230;
						lbl->TextAlign = ContentAlignment::MiddleCenter;

						if (text->StartsWith("Name:")) {
							lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Bold);
						}
						else {
							lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0F, FontStyle::Regular);
						}

						innerPanel->Controls->Add(lbl);
					}

					Panel^ quantityRow = gcnew Panel();
					quantityRow->Width = 230;
					quantityRow->Height = 30;

					Label^ lblQty = gcnew Label();
					lblQty->Text = "Quantity:";
					lblQty->Width = 70;
					lblQty->Height = 22;
					lblQty->Location = Point(0, 4);
					lblQty->TextAlign = ContentAlignment::MiddleRight;

					NumericUpDown^ quantityBox = gcnew NumericUpDown();
					quantityBox->Minimum = 0;
					quantityBox->Maximum = 10;
					quantityBox->DecimalPlaces = 2;
					quantityBox->Size = Drawing::Size(140, 22);
					quantityBox->Location = Point(80, 4);

					quantityRow->Controls->Add(lblQty);
					quantityRow->Controls->Add(quantityBox);
					innerPanel->Controls->Add(quantityRow);

					Button^ btnAdd = gcnew Button();
					btnAdd->Text = "Add to Cart";
					btnAdd->Width = 230;
					btnAdd->Height = 35;
					btnAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, FontStyle::Regular));
					btnAdd->BackColor = Color::FromArgb(230, 52, 98);
					btnAdd->ForeColor = Color::White;
					btnAdd->Click += gcnew EventHandler(this, &MyForm::handleAddToCart);

					innerPanel->Controls->Add(btnAdd);

					productPanel->Controls->Add(innerPanel);
					panelToFill->Controls->Add(productPanel);
				}

				reader->Close();
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error loading category: " + categoryFilter + "\n" + ex->Message);
			}
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ pn_upper_bar;
	protected:

	private: System::Windows::Forms::Button^ btn_close;
	private: System::Windows::Forms::Button^ btn_minimize;
	private: System::Windows::Forms::Panel^ pn_main_dashboard;
	private: System::Windows::Forms::Panel^ pn_start;
	private: System::Windows::Forms::Panel^ pn_login;
	private: System::Windows::Forms::Panel^ pn_register;
	private: System::Windows::Forms::Panel^ pn_thankyou;
	private: System::Windows::Forms::Panel^ pn_defualt;
	private: System::Windows::Forms::Panel^ pn_left_bar;
	private: System::Windows::Forms::Panel^ pn_orders;
	private: System::Windows::Forms::Panel^ pn_products;
	private: System::Windows::Forms::Panel^ pn_edit_information;
	private: System::Windows::Forms::PictureBox^ pb_icon;
	private: System::Windows::Forms::Label^ lb_brand_name;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel1;
	private: System::Windows::Forms::Button^ btn_edit_information;
	private: System::Windows::Forms::Panel^ pn_picture;
	private: System::Windows::Forms::Button^ btn_products;
	private: System::Windows::Forms::Button^ btn_orders;
	private: System::Windows::Forms::Button^ btn_login;
	private: System::Windows::Forms::Label^ lb_profile;
	private: System::Windows::Forms::PictureBox^ pb_profile;
	private: System::Windows::Forms::Panel^ pn_blank;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ btn_exit;
	private: System::Windows::Forms::Button^ btn_start;
	private: System::Windows::Forms::Button^ btn_login_loginpanel;
	private: System::Windows::Forms::Button^ btn_register_loginpanel;
	private: System::Windows::Forms::Button^ btn_back_loginpanal;
	private: System::Windows::Forms::Panel^ pn_vegetable;
	private: System::Windows::Forms::Panel^ pn_dairy;
	private: System::Windows::Forms::Panel^ pn_butcher_shop;
	private: System::Windows::Forms::Panel^ pn_seafood;
	private: System::Windows::Forms::Panel^ pn_;
	private: System::Windows::Forms::Panel^ pn_butchershop_category;
	private: System::Windows::Forms::Panel^ pn_seafood_category;
    private: System::Windows::Forms::Panel^ pn_pet_supplies_category;
	private: System::Windows::Forms::Panel^ pn_dairy_category;
	private: System::Windows::Forms::Panel^ pn_fruits;
	private: System::Windows::Forms::Panel^ pn_main_category;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::Button^ btn_fruits;
	private: System::Windows::Forms::PictureBox^ welcomeScreen;
	private: System::Windows::Forms::Button^ btn_category_household;
	private: System::Windows::Forms::Button^ btn_category_pet_supplies;
	private: System::Windows::Forms::TextBox^ tb_password_login;
	private: System::Windows::Forms::TextBox^ tb_username_login;
	private: System::Windows::Forms::Label^ lb_password;
	private: System::Windows::Forms::Label^ lb_username;
	private: System::Windows::Forms::Label^ lb_password_register;
	private: System::Windows::Forms::Label^ lb_phonenumber_register;
	private: System::Windows::Forms::Label^ lb_location;
	private: System::Windows::Forms::Label^ lb_username_register;
	private: System::Windows::Forms::TextBox^ tb_location_register;
	private: System::Windows::Forms::TextBox^ tb_phonenumber_register;
	private: System::Windows::Forms::TextBox^ tb_password_register;
	private: System::Windows::Forms::TextBox^ tb_username_register;
	private: System::Windows::Forms::Button^ btn_register_registerpanel;
	private: System::Windows::Forms::PictureBox^ pb_blankpicutre;
	private: System::Windows::Forms::Label^ lb_username_message;
	private: System::Windows::Forms::Label^ lb_location_message;
	private: System::Windows::Forms::Label^ lb_phonenumber_message;
	private: System::Windows::Forms::Label^ lb_password_message;
	private: System::Windows::Forms::Button^ btn_seepassword;
	private: System::Windows::Forms::Button^ btn_refresh_username_register;
	private: System::Windows::Forms::Button^ btn_refresh_location_register;
	private: System::Windows::Forms::Button^ btn_refresh_phonenumber_register;
	private: System::Windows::Forms::Button^ btn_refresh_password_register;
	private: System::Windows::Forms::Button^ btn_refresh_password_login;
	private: System::Windows::Forms::Button^ btn_refresh_username_login;
	private: System::Windows::Forms::Button^ btn_seepasword_login;
	private: System::Windows::Forms::Label^ lb_password_message_login;
	private: System::Windows::Forms::Label^ lb_username_message_login;
	private: System::Windows::Forms::Panel^ pn_fruits_category;
	private: System::Windows::Forms::Panel^ pn_vegetable_category;
	private: System::Windows::Forms::Panel^ pn_bakery_category;
	private: System::Windows::Forms::Panel^ pn_household_category;
	private: System::Windows::Forms::Panel^ pn_snacks_category;
	private: System::Windows::Forms::Panel^ pn_poultry_category;
	private: System::Windows::Forms::Button^ btn_vegetabe;
	private: System::Windows::Forms::Button^ btn_dairy;
	private: System::Windows::Forms::Button^ btn_butcher;
	private: System::Windows::Forms::Button^ btn_seafood;
	private: System::Windows::Forms::Button^ btn_poultry;
	private: System::Windows::Forms::Button^ btn_bakery;
	private: System::Windows::Forms::Button^ btn_snacks;
	private: System::Windows::Forms::Button^ btn_household;
	private: System::Windows::Forms::Button^ btn_pet;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::PictureBox^ pictureBox2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel3;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel12;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel11;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel10;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel9;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel8;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel7;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel6;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel5;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel4;
	private: System::Windows::Forms::Panel^ pn_currentInfo;
	private: System::Windows::Forms::Panel^ pn_resetPassword;
	private: System::Windows::Forms::Panel^ pn_editInfo;
	private: System::Windows::Forms::TextBox^ tb_currentUsername;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Button^ btn_editInfo;
	private: System::Windows::Forms::TextBox^ tb_currentPassword;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ tb_currentPhoneNumber;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ tb_currentLocation;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ btn_cancelEdit;
	private: System::Windows::Forms::Button^ btn_saveEdit;
	private: System::Windows::Forms::TextBox^ tb_edit_phonenumber;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::TextBox^ tb_edit_location;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::TextBox^ tb_edit_username;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ btn_saveResetPassword;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ tb_newPassword;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Button^ btn_reset;
	private: System::Windows::Forms::Button^ btn_seepassword_editinfo;
	private: System::Windows::Forms::TextBox^ tb_confirmPassword;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Button^ btn_TotalBill;
	private: System::Windows::Forms::Panel^ pn_viewBill;
    private: System::Windows::Forms::Label^ lb_theinvoice;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Timer^ timerforexit;
    private: System::Windows::Forms::FlowLayoutPanel^ orderList;
    private: System::Windows::Forms::Button^ link_login;
    private: System::Windows::Forms::PictureBox^ pb_theinvoice;
    private: System::Windows::Forms::Panel^ pn;
    private: System::Windows::Forms::Label^ lb_invoicenumber_theinvoice;
    private: System::Windows::Forms::Label^ lb_date_theinvice;
    private: System::Windows::Forms::TextBox^ tb_date_theinvoice;
    private: System::Windows::Forms::TextBox^ tb_invoicenumber_theinvoice;
	private: System::Windows::Forms::TextBox^ tb_customername_theincoive;
	private: System::Windows::Forms::Label^ lb_customername_theinvoice;
	private: System::Windows::Forms::DataGridView^ dataGridView1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colproduct;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colquantity;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colunitprice;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ colsubtotal;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel13;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Label^ lb_beforevat;
	private: System::Windows::Forms::Label^ lb_beforevat_number;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::Button^ btn_print;
	private: System::Windows::Forms::PrintPreviewDialog^ printPreviewDialog1;
	private: System::Drawing::Printing::PrintDocument^ printDocument1;
	private: System::Windows::Forms::Label^ lb_total;
	private: System::Windows::Forms::Label^ lb_shipping;
	private: System::Windows::Forms::Label^ lb_vat;
	private: System::Windows::Forms::Label^ lb_discount;
	private: System::Windows::Forms::Label^ lb_shipping_number;
	private: System::Windows::Forms::Label^ lb_vat_number;
	private: System::Windows::Forms::Label^ lb_discount_number;
	private: System::Windows::Forms::Label^ lb_total_number;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::PictureBox^ pictureBox3;
	private: System::Windows::Forms::PictureBox^ pictureBox4;
	private: System::Windows::Forms::PictureBox^ pictureBox5;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::Label^ label25;

	private: System::Windows::Forms::PictureBox^ pictureBox8;
	private: System::Windows::Forms::PictureBox^ pictureBox7;
	private: System::Windows::Forms::PictureBox^ pictureBox9;
	private: System::Windows::Forms::PictureBox^ pictureBox10;
	private: System::Windows::Forms::PictureBox^ pictureBox12;
	private: System::Windows::Forms::PictureBox^ pictureBox11;
	private: System::Windows::Forms::PictureBox^ pictureBox13;
	private: AxWMPLib::AxWindowsMediaPlayer^ axWindowsMediaPlayer1;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ lb_newpassword;
	private: System::Windows::Forms::Label^ lb_errorUsername;
	private: System::Windows::Forms::Label^ lb_errorLocation;
	private: System::Windows::Forms::Label^ lb_errorPhone;

	private: System::ComponentModel::IContainer^ components;
	protected:
	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pn_upper_bar = (gcnew System::Windows::Forms::Panel());
			this->lb_brand_name = (gcnew System::Windows::Forms::Label());
			this->pb_icon = (gcnew System::Windows::Forms::PictureBox());
			this->btn_minimize = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->pn_main_dashboard = (gcnew System::Windows::Forms::Panel());
			this->pn_login = (gcnew System::Windows::Forms::Panel());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->pictureBox8 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox7 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lb_password_message_login = (gcnew System::Windows::Forms::Label());
			this->lb_username_message_login = (gcnew System::Windows::Forms::Label());
			this->btn_refresh_password_login = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_username_login = (gcnew System::Windows::Forms::Button());
			this->btn_seepasword_login = (gcnew System::Windows::Forms::Button());
			this->tb_password_login = (gcnew System::Windows::Forms::TextBox());
			this->tb_username_login = (gcnew System::Windows::Forms::TextBox());
			this->lb_password = (gcnew System::Windows::Forms::Label());
			this->lb_username = (gcnew System::Windows::Forms::Label());
			this->btn_register_loginpanel = (gcnew System::Windows::Forms::Button());
			this->btn_back_loginpanal = (gcnew System::Windows::Forms::Button());
			this->btn_login_loginpanel = (gcnew System::Windows::Forms::Button());
			this->pn_defualt = (gcnew System::Windows::Forms::Panel());
			this->pn_edit_information = (gcnew System::Windows::Forms::Panel());
			this->pn_currentInfo = (gcnew System::Windows::Forms::Panel());
			this->pictureBox13 = (gcnew System::Windows::Forms::PictureBox());
			this->btn_seepassword_editinfo = (gcnew System::Windows::Forms::Button());
			this->btn_reset = (gcnew System::Windows::Forms::Button());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->btn_editInfo = (gcnew System::Windows::Forms::Button());
			this->tb_currentPassword = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tb_currentPhoneNumber = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->tb_currentLocation = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->tb_currentUsername = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pn_editInfo = (gcnew System::Windows::Forms::Panel());
			this->lb_errorLocation = (gcnew System::Windows::Forms::Label());
			this->lb_errorPhone = (gcnew System::Windows::Forms::Label());
			this->lb_errorUsername = (gcnew System::Windows::Forms::Label());
			this->pictureBox11 = (gcnew System::Windows::Forms::PictureBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->btn_cancelEdit = (gcnew System::Windows::Forms::Button());
			this->btn_saveEdit = (gcnew System::Windows::Forms::Button());
			this->tb_edit_phonenumber = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tb_edit_location = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tb_edit_username = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->pn_resetPassword = (gcnew System::Windows::Forms::Panel());
			this->lb_newpassword = (gcnew System::Windows::Forms::Label());
			this->pictureBox12 = (gcnew System::Windows::Forms::PictureBox());
			this->tb_confirmPassword = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->btn_saveResetPassword = (gcnew System::Windows::Forms::Button());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tb_newPassword = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pn_blank = (gcnew System::Windows::Forms::Panel());
			this->pb_blankpicutre = (gcnew System::Windows::Forms::PictureBox());
			this->pn_products = (gcnew System::Windows::Forms::Panel());
			this->pn_main_category = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btn_fruits = (gcnew System::Windows::Forms::Button());
			this->btn_vegetabe = (gcnew System::Windows::Forms::Button());
			this->btn_dairy = (gcnew System::Windows::Forms::Button());
			this->btn_butcher = (gcnew System::Windows::Forms::Button());
			this->btn_seafood = (gcnew System::Windows::Forms::Button());
			this->btn_poultry = (gcnew System::Windows::Forms::Button());
			this->btn_bakery = (gcnew System::Windows::Forms::Button());
			this->btn_snacks = (gcnew System::Windows::Forms::Button());
			this->btn_household = (gcnew System::Windows::Forms::Button());
			this->btn_pet = (gcnew System::Windows::Forms::Button());
			this->pn_pet_supplies_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel12 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_household_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel11 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_snacks_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel10 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_bakery_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel9 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_poultry_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel8 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_seafood_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel7 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_butchershop_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel6 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_dairy_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel5 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_vegetable_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel4 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_fruits_category = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel3 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_orders = (gcnew System::Windows::Forms::Panel());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->orderList = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->pn_viewBill = (gcnew System::Windows::Forms::Panel());
			this->pb_theinvoice = (gcnew System::Windows::Forms::PictureBox());
			this->pn = (gcnew System::Windows::Forms::Panel());
			this->btn_print = (gcnew System::Windows::Forms::Button());
			this->flowLayoutPanel13 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			this->colproduct = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colquantity = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colunitprice = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->colsubtotal = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->lb_total_number = (gcnew System::Windows::Forms::Label());
			this->lb_shipping_number = (gcnew System::Windows::Forms::Label());
			this->lb_vat_number = (gcnew System::Windows::Forms::Label());
			this->lb_discount_number = (gcnew System::Windows::Forms::Label());
			this->lb_shipping = (gcnew System::Windows::Forms::Label());
			this->lb_vat = (gcnew System::Windows::Forms::Label());
			this->lb_discount = (gcnew System::Windows::Forms::Label());
			this->lb_total = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->lb_beforevat_number = (gcnew System::Windows::Forms::Label());
			this->lb_beforevat = (gcnew System::Windows::Forms::Label());
			this->tb_customername_theincoive = (gcnew System::Windows::Forms::TextBox());
			this->lb_customername_theinvoice = (gcnew System::Windows::Forms::Label());
			this->tb_date_theinvoice = (gcnew System::Windows::Forms::TextBox());
			this->tb_invoicenumber_theinvoice = (gcnew System::Windows::Forms::TextBox());
			this->lb_date_theinvice = (gcnew System::Windows::Forms::Label());
			this->lb_invoicenumber_theinvoice = (gcnew System::Windows::Forms::Label());
			this->lb_theinvoice = (gcnew System::Windows::Forms::Label());
			this->pn_left_bar = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btn_edit_information = (gcnew System::Windows::Forms::Button());
			this->btn_products = (gcnew System::Windows::Forms::Button());
			this->btn_orders = (gcnew System::Windows::Forms::Button());
			this->btn_TotalBill = (gcnew System::Windows::Forms::Button());
			this->btn_login = (gcnew System::Windows::Forms::Button());
			this->pn_picture = (gcnew System::Windows::Forms::Panel());
			this->lb_profile = (gcnew System::Windows::Forms::Label());
			this->pb_profile = (gcnew System::Windows::Forms::PictureBox());
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->pictureBox5 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox4 = (gcnew System::Windows::Forms::PictureBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->btn_exit = (gcnew System::Windows::Forms::Button());
			this->welcomeScreen = (gcnew System::Windows::Forms::PictureBox());
			this->pn_register = (gcnew System::Windows::Forms::Panel());
			this->pictureBox9 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox10 = (gcnew System::Windows::Forms::PictureBox());
			this->link_login = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btn_refresh_location_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_phonenumber_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_password_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_username_register = (gcnew System::Windows::Forms::Button());
			this->btn_seepassword = (gcnew System::Windows::Forms::Button());
			this->lb_location_message = (gcnew System::Windows::Forms::Label());
			this->lb_phonenumber_message = (gcnew System::Windows::Forms::Label());
			this->lb_password_message = (gcnew System::Windows::Forms::Label());
			this->lb_username_message = (gcnew System::Windows::Forms::Label());
			this->btn_register_registerpanel = (gcnew System::Windows::Forms::Button());
			this->tb_location_register = (gcnew System::Windows::Forms::TextBox());
			this->tb_phonenumber_register = (gcnew System::Windows::Forms::TextBox());
			this->tb_password_register = (gcnew System::Windows::Forms::TextBox());
			this->tb_username_register = (gcnew System::Windows::Forms::TextBox());
			this->lb_password_register = (gcnew System::Windows::Forms::Label());
			this->lb_phonenumber_register = (gcnew System::Windows::Forms::Label());
			this->lb_location = (gcnew System::Windows::Forms::Label());
			this->lb_username_register = (gcnew System::Windows::Forms::Label());
			this->pn_thankyou = (gcnew System::Windows::Forms::Panel());
			this->axWindowsMediaPlayer1 = (gcnew AxWMPLib::AxWindowsMediaPlayer());
			this->timerforexit = (gcnew System::Windows::Forms::Timer(this->components));
			this->printPreviewDialog1 = (gcnew System::Windows::Forms::PrintPreviewDialog());
			this->printDocument1 = (gcnew System::Drawing::Printing::PrintDocument());
			this->pn_upper_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->BeginInit();
			this->pn_main_dashboard->SuspendLayout();
			this->pn_login->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->pn_defualt->SuspendLayout();
			this->pn_edit_information->SuspendLayout();
			this->pn_currentInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->BeginInit();
			this->pn_editInfo->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->BeginInit();
			this->pn_resetPassword->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->BeginInit();
			this->pn_blank->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->BeginInit();
			this->pn_products->SuspendLayout();
			this->pn_main_category->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->pn_pet_supplies_category->SuspendLayout();
			this->pn_household_category->SuspendLayout();
			this->pn_snacks_category->SuspendLayout();
			this->pn_bakery_category->SuspendLayout();
			this->pn_poultry_category->SuspendLayout();
			this->pn_seafood_category->SuspendLayout();
			this->pn_butchershop_category->SuspendLayout();
			this->pn_dairy_category->SuspendLayout();
			this->pn_vegetable_category->SuspendLayout();
			this->pn_fruits_category->SuspendLayout();
			this->pn_orders->SuspendLayout();
			this->pn_viewBill->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_theinvoice))->BeginInit();
			this->pn->SuspendLayout();
			this->flowLayoutPanel13->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			this->panel2->SuspendLayout();
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_picture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->BeginInit();
			this->pn_start->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->BeginInit();
			this->pn_register->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->pn_thankyou->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->BeginInit();
			this->SuspendLayout();
			// 
			// pn_upper_bar
			// 
			this->pn_upper_bar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_upper_bar->Controls->Add(this->lb_brand_name);
			this->pn_upper_bar->Controls->Add(this->pb_icon);
			this->pn_upper_bar->Controls->Add(this->btn_minimize);
			this->pn_upper_bar->Controls->Add(this->btn_close);
			this->pn_upper_bar->Dock = System::Windows::Forms::DockStyle::Top;
			this->pn_upper_bar->Location = System::Drawing::Point(0, 0);
			this->pn_upper_bar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_upper_bar->Name = L"pn_upper_bar";
			this->pn_upper_bar->Size = System::Drawing::Size(1485, 55);
			this->pn_upper_bar->TabIndex = 0;
			// 
			// lb_brand_name
			// 
			this->lb_brand_name->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_brand_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(134)),
				static_cast<System::Int32>(static_cast<System::Byte>(6)));
			this->lb_brand_name->Location = System::Drawing::Point(76, 6);
			this->lb_brand_name->Name = L"lb_brand_name";
			this->lb_brand_name->Size = System::Drawing::Size(251, 43);
			this->lb_brand_name->TabIndex = 4;
			this->lb_brand_name->Text = L"SUPERMARKO";
			// 
			// pb_icon
			// 
			this->pb_icon->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_icon.BackgroundImage")));
			this->pb_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pb_icon->Location = System::Drawing::Point(3, 2);
			this->pb_icon->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pb_icon->Name = L"pb_icon";
			this->pb_icon->Size = System::Drawing::Size(93, 50);
			this->pb_icon->TabIndex = 3;
			this->pb_icon->TabStop = false;
			// 
			// btn_minimize
			// 
			this->btn_minimize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btn_minimize->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_minimize.BackgroundImage")));
			this->btn_minimize->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_minimize->FlatAppearance->BorderSize = 0;
			this->btn_minimize->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(102)),
				static_cast<System::Int32>(static_cast<System::Byte>(106)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->btn_minimize->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(127)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->btn_minimize->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_minimize->Location = System::Drawing::Point(1343, 5);
			this->btn_minimize->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_minimize->Name = L"btn_minimize";
			this->btn_minimize->Size = System::Drawing::Size(65, 46);
			this->btn_minimize->TabIndex = 2;
			this->btn_minimize->UseVisualStyleBackColor = true;
			this->btn_minimize->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// btn_close
			// 
			this->btn_close->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btn_close->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_close.BackgroundImage")));
			this->btn_close->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_close->FlatAppearance->BorderSize = 0;
			this->btn_close->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(102)),
				static_cast<System::Int32>(static_cast<System::Byte>(106)), static_cast<System::Int32>(static_cast<System::Byte>(120)));
			this->btn_close->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(127)),
				static_cast<System::Int32>(static_cast<System::Byte>(131)), static_cast<System::Int32>(static_cast<System::Byte>(145)));
			this->btn_close->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_close->Location = System::Drawing::Point(1401, 5);
			this->btn_close->Margin = System::Windows::Forms::Padding(5);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(80, 46);
			this->btn_close->TabIndex = 1;
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &MyForm::btn_close_Click);
			// 
			// pn_main_dashboard
			// 
			this->pn_main_dashboard->AllowDrop = true;
			this->pn_main_dashboard->Controls->Add(this->pn_register);
			this->pn_main_dashboard->Controls->Add(this->pn_login);
			this->pn_main_dashboard->Controls->Add(this->pn_defualt);
			this->pn_main_dashboard->Controls->Add(this->pn_start);
			this->pn_main_dashboard->Controls->Add(this->pn_thankyou);
			this->pn_main_dashboard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_dashboard->Location = System::Drawing::Point(0, 55);
			this->pn_main_dashboard->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_main_dashboard->Name = L"pn_main_dashboard";
			this->pn_main_dashboard->Size = System::Drawing::Size(1485, 745);
			this->pn_main_dashboard->TabIndex = 1;
			// 
			// pn_login
			// 
			this->pn_login->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_login->Controls->Add(this->label26);
			this->pn_login->Controls->Add(this->pictureBox8);
			this->pn_login->Controls->Add(this->pictureBox7);
			this->pn_login->Controls->Add(this->pictureBox2);
			this->pn_login->Controls->Add(this->label3);
			this->pn_login->Controls->Add(this->lb_password_message_login);
			this->pn_login->Controls->Add(this->lb_username_message_login);
			this->pn_login->Controls->Add(this->btn_refresh_password_login);
			this->pn_login->Controls->Add(this->btn_refresh_username_login);
			this->pn_login->Controls->Add(this->btn_seepasword_login);
			this->pn_login->Controls->Add(this->tb_password_login);
			this->pn_login->Controls->Add(this->tb_username_login);
			this->pn_login->Controls->Add(this->lb_password);
			this->pn_login->Controls->Add(this->lb_username);
			this->pn_login->Controls->Add(this->btn_register_loginpanel);
			this->pn_login->Controls->Add(this->btn_back_loginpanal);
			this->pn_login->Controls->Add(this->btn_login_loginpanel);
			this->pn_login->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_login->Location = System::Drawing::Point(0, 0);
			this->pn_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_login->Name = L"pn_login";
			this->pn_login->Size = System::Drawing::Size(1485, 745);
			this->pn_login->TabIndex = 2;
			// 
			// label26
			// 
			this->label26->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::Color::White;
			this->label26->Location = System::Drawing::Point(661, 420);
			this->label26->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(268, 28);
			this->label26->TabIndex = 26;
			this->label26->Text = L"You don\'t have an account\?";
			// 
			// pictureBox8
			// 
			this->pictureBox8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox8.Image")));
			this->pictureBox8->Location = System::Drawing::Point(-39, 507);
			this->pictureBox8->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox8->Name = L"pictureBox8";
			this->pictureBox8->Size = System::Drawing::Size(432, 343);
			this->pictureBox8->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox8->TabIndex = 25;
			this->pictureBox8->TabStop = false;
			// 
			// pictureBox7
			// 
			this->pictureBox7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox7.Image")));
			this->pictureBox7->Location = System::Drawing::Point(1093, 507);
			this->pictureBox7->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox7->Name = L"pictureBox7";
			this->pictureBox7->Size = System::Drawing::Size(432, 343);
			this->pictureBox7->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox7->TabIndex = 24;
			this->pictureBox7->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(588, 54);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(87, 62);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox2->TabIndex = 23;
			this->pictureBox2->TabStop = false;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(684, 48);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(213, 68);
			this->label3->TabIndex = 22;
			this->label3->Text = L"Login";
			// 
			// lb_password_message_login
			// 
			this->lb_password_message_login->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_message_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_message_login->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_password_message_login->Location = System::Drawing::Point(653, 362);
			this->lb_password_message_login->Name = L"lb_password_message_login";
			this->lb_password_message_login->Size = System::Drawing::Size(325, 23);
			this->lb_password_message_login->TabIndex = 21;
			this->lb_password_message_login->Text = L"Please enter the password";
			this->lb_password_message_login->Visible = false;
			// 
			// lb_username_message_login
			// 
			this->lb_username_message_login->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_message_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_message_login->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_username_message_login->Location = System::Drawing::Point(648, 252);
			this->lb_username_message_login->Name = L"lb_username_message_login";
			this->lb_username_message_login->Size = System::Drawing::Size(325, 23);
			this->lb_username_message_login->TabIndex = 20;
			this->lb_username_message_login->Text = L" Please enter the username";
			this->lb_username_message_login->Visible = false;
			// 
			// btn_refresh_password_login
			// 
			this->btn_refresh_password_login->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_password_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_password_login.BackgroundImage")));
			this->btn_refresh_password_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_password_login->FlatAppearance->BorderSize = 0;
			this->btn_refresh_password_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_password_login->Location = System::Drawing::Point(995, 331);
			this->btn_refresh_password_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_password_login->Name = L"btn_refresh_password_login";
			this->btn_refresh_password_login->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_password_login->TabIndex = 19;
			this->btn_refresh_password_login->UseVisualStyleBackColor = false;
			this->btn_refresh_password_login->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_password_login_Click);
			// 
			// btn_refresh_username_login
			// 
			this->btn_refresh_username_login->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_username_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_username_login.BackgroundImage")));
			this->btn_refresh_username_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_username_login->FlatAppearance->BorderSize = 0;
			this->btn_refresh_username_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_username_login->ForeColor = System::Drawing::Color::White;
			this->btn_refresh_username_login->Location = System::Drawing::Point(995, 217);
			this->btn_refresh_username_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_username_login->Name = L"btn_refresh_username_login";
			this->btn_refresh_username_login->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_username_login->TabIndex = 18;
			this->btn_refresh_username_login->UseVisualStyleBackColor = false;
			this->btn_refresh_username_login->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_username_login_Click);
			// 
			// btn_seepasword_login
			// 
			this->btn_seepasword_login->BackColor = System::Drawing::Color::White;
			this->btn_seepasword_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepasword_login.BackgroundImage")));
			this->btn_seepasword_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepasword_login->FlatAppearance->BorderSize = 0;
			this->btn_seepasword_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepasword_login->Location = System::Drawing::Point(940, 324);
			this->btn_seepasword_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_seepasword_login->Name = L"btn_seepasword_login";
			this->btn_seepasword_login->Size = System::Drawing::Size(33, 34);
			this->btn_seepasword_login->TabIndex = 15;
			this->btn_seepasword_login->UseVisualStyleBackColor = false;
			this->btn_seepasword_login->Click += gcnew System::EventHandler(this, &MyForm::btn_seepasword_login_Click);
			// 
			// tb_password_login
			// 
			this->tb_password_login->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_password_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tb_password_login->Location = System::Drawing::Point(645, 322);
			this->tb_password_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_password_login->Name = L"tb_password_login";
			this->tb_password_login->Size = System::Drawing::Size(330, 37);
			this->tb_password_login->TabIndex = 1;
			this->tb_password_login->UseSystemPasswordChar = true;
			// 
			// tb_username_login
			// 
			this->tb_username_login->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_username_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 15.75F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tb_username_login->Location = System::Drawing::Point(645, 210);
			this->tb_username_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_username_login->Name = L"tb_username_login";
			this->tb_username_login->Size = System::Drawing::Size(330, 37);
			this->tb_username_login->TabIndex = 0;
			// 
			// lb_password
			// 
			this->lb_password->BackColor = System::Drawing::Color::Transparent;
			this->lb_password->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_password->ForeColor = System::Drawing::Color::White;
			this->lb_password->Location = System::Drawing::Point(452, 319);
			this->lb_password->Name = L"lb_password";
			this->lb_password->Size = System::Drawing::Size(177, 34);
			this->lb_password->TabIndex = 4;
			this->lb_password->Text = L"Password";
			// 
			// lb_username
			// 
			this->lb_username->BackColor = System::Drawing::Color::Transparent;
			this->lb_username->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_username->ForeColor = System::Drawing::Color::White;
			this->lb_username->Location = System::Drawing::Point(452, 206);
			this->lb_username->Name = L"lb_username";
			this->lb_username->Size = System::Drawing::Size(177, 34);
			this->lb_username->TabIndex = 3;
			this->lb_username->Text = L"Username";
			// 
			// btn_register_loginpanel
			// 
			this->btn_register_loginpanel->BackColor = System::Drawing::Color::LightCoral;
			this->btn_register_loginpanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_register_loginpanel->FlatAppearance->BorderSize = 0;
			this->btn_register_loginpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_register_loginpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_register_loginpanel->ForeColor = System::Drawing::Color::White;
			this->btn_register_loginpanel->Location = System::Drawing::Point(936, 412);
			this->btn_register_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_register_loginpanel->Name = L"btn_register_loginpanel";
			this->btn_register_loginpanel->Size = System::Drawing::Size(124, 37);
			this->btn_register_loginpanel->TabIndex = 3;
			this->btn_register_loginpanel->Text = L"Register";
			this->btn_register_loginpanel->UseVisualStyleBackColor = false;
			this->btn_register_loginpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_register_loginpanel_Click);
			// 
			// btn_back_loginpanal
			// 
			this->btn_back_loginpanal->BackColor = System::Drawing::Color::DarkGray;
			this->btn_back_loginpanal->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_back_loginpanal->FlatAppearance->BorderSize = 0;
			this->btn_back_loginpanal->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_back_loginpanal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_back_loginpanal->ForeColor = System::Drawing::Color::White;
			this->btn_back_loginpanal->Location = System::Drawing::Point(664, 607);
			this->btn_back_loginpanal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_back_loginpanal->Name = L"btn_back_loginpanal";
			this->btn_back_loginpanal->Size = System::Drawing::Size(152, 53);
			this->btn_back_loginpanal->TabIndex = 4;
			this->btn_back_loginpanal->Text = L"Back";
			this->btn_back_loginpanal->UseVisualStyleBackColor = false;
			this->btn_back_loginpanal->Click += gcnew System::EventHandler(this, &MyForm::btn_back_loginpanal_Click);
			// 
			// btn_login_loginpanel
			// 
			this->btn_login_loginpanel->BackColor = System::Drawing::Color::Turquoise;
			this->btn_login_loginpanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_login_loginpanel->FlatAppearance->BorderSize = 0;
			this->btn_login_loginpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_login_loginpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 17.25F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_login_loginpanel->ForeColor = System::Drawing::Color::White;
			this->btn_login_loginpanel->Location = System::Drawing::Point(625, 519);
			this->btn_login_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_login_loginpanel->Name = L"btn_login_loginpanel";
			this->btn_login_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_login_loginpanel->TabIndex = 2;
			this->btn_login_loginpanel->Text = L"Log in";
			this->btn_login_loginpanel->UseVisualStyleBackColor = false;
			this->btn_login_loginpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_login_loginpanel_Click);
			// 
			// pn_defualt
			// 
			this->pn_defualt->Controls->Add(this->pn_edit_information);
			this->pn_defualt->Controls->Add(this->pn_blank);
			this->pn_defualt->Controls->Add(this->pn_products);
			this->pn_defualt->Controls->Add(this->pn_orders);
			this->pn_defualt->Controls->Add(this->pn_viewBill);
			this->pn_defualt->Controls->Add(this->pn_left_bar);
			this->pn_defualt->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_defualt->Location = System::Drawing::Point(0, 0);
			this->pn_defualt->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_defualt->Name = L"pn_defualt";
			this->pn_defualt->Size = System::Drawing::Size(1485, 745);
			this->pn_defualt->TabIndex = 4;
			// 
			// pn_edit_information
			// 
			this->pn_edit_information->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pn_edit_information->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)));
			this->pn_edit_information->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pn_edit_information->Controls->Add(this->pn_currentInfo);
			this->pn_edit_information->Controls->Add(this->pn_editInfo);
			this->pn_edit_information->Controls->Add(this->pn_resetPassword);
			this->pn_edit_information->Controls->Add(this->label1);
			this->pn_edit_information->Location = System::Drawing::Point(296, 0);
			this->pn_edit_information->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_edit_information->Name = L"pn_edit_information";
			this->pn_edit_information->Size = System::Drawing::Size(1189, 745);
			this->pn_edit_information->TabIndex = 1;
			// 
			// pn_currentInfo
			// 
			this->pn_currentInfo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_currentInfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pn_currentInfo->Controls->Add(this->pictureBox13);
			this->pn_currentInfo->Controls->Add(this->btn_seepassword_editinfo);
			this->pn_currentInfo->Controls->Add(this->btn_reset);
			this->pn_currentInfo->Controls->Add(this->label16);
			this->pn_currentInfo->Controls->Add(this->btn_editInfo);
			this->pn_currentInfo->Controls->Add(this->tb_currentPassword);
			this->pn_currentInfo->Controls->Add(this->label8);
			this->pn_currentInfo->Controls->Add(this->tb_currentPhoneNumber);
			this->pn_currentInfo->Controls->Add(this->label7);
			this->pn_currentInfo->Controls->Add(this->tb_currentLocation);
			this->pn_currentInfo->Controls->Add(this->label6);
			this->pn_currentInfo->Controls->Add(this->tb_currentUsername);
			this->pn_currentInfo->Controls->Add(this->label5);
			this->pn_currentInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_currentInfo->Location = System::Drawing::Point(0, 147);
			this->pn_currentInfo->Margin = System::Windows::Forms::Padding(4);
			this->pn_currentInfo->Name = L"pn_currentInfo";
			this->pn_currentInfo->Size = System::Drawing::Size(1189, 598);
			this->pn_currentInfo->TabIndex = 1;
			// 
			// pictureBox13
			// 
			this->pictureBox13->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox13.Image")));
			this->pictureBox13->Location = System::Drawing::Point(433, 30);
			this->pictureBox13->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox13->Name = L"pictureBox13";
			this->pictureBox13->Size = System::Drawing::Size(51, 37);
			this->pictureBox13->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox13->TabIndex = 24;
			this->pictureBox13->TabStop = false;
			// 
			// btn_seepassword_editinfo
			// 
			this->btn_seepassword_editinfo->BackColor = System::Drawing::SystemColors::Control;
			this->btn_seepassword_editinfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepassword_editinfo.BackgroundImage")));
			this->btn_seepassword_editinfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepassword_editinfo->FlatAppearance->BorderSize = 0;
			this->btn_seepassword_editinfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepassword_editinfo->Location = System::Drawing::Point(917, 316);
			this->btn_seepassword_editinfo->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_seepassword_editinfo->Name = L"btn_seepassword_editinfo";
			this->btn_seepassword_editinfo->Size = System::Drawing::Size(41, 22);
			this->btn_seepassword_editinfo->TabIndex = 23;
			this->btn_seepassword_editinfo->UseVisualStyleBackColor = false;
			this->btn_seepassword_editinfo->Click += gcnew System::EventHandler(this, &MyForm::btn_seepassword_editinfo_Click);
			// 
			// btn_reset
			// 
			this->btn_reset->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_reset->FlatAppearance->BorderSize = 0;
			this->btn_reset->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_reset->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_reset->ForeColor = System::Drawing::Color::Black;
			this->btn_reset->Location = System::Drawing::Point(557, 416);
			this->btn_reset->Margin = System::Windows::Forms::Padding(4);
			this->btn_reset->Name = L"btn_reset";
			this->btn_reset->Size = System::Drawing::Size(248, 66);
			this->btn_reset->TabIndex = 22;
			this->btn_reset->Text = L"Reset Password";
			this->btn_reset->UseVisualStyleBackColor = false;
			this->btn_reset->Click += gcnew System::EventHandler(this, &MyForm::btn_reset_Click);
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label16->Location = System::Drawing::Point(492, 25);
			this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(191, 41);
			this->label16->TabIndex = 21;
			this->label16->Text = L"Current Info";
			// 
			// btn_editInfo
			// 
			this->btn_editInfo->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->btn_editInfo->FlatAppearance->BorderSize = 3;
			this->btn_editInfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_editInfo->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_editInfo->Location = System::Drawing::Point(385, 416);
			this->btn_editInfo->Margin = System::Windows::Forms::Padding(4);
			this->btn_editInfo->Name = L"btn_editInfo";
			this->btn_editInfo->Size = System::Drawing::Size(131, 66);
			this->btn_editInfo->TabIndex = 8;
			this->btn_editInfo->Text = L"Edit";
			this->btn_editInfo->UseVisualStyleBackColor = true;
			this->btn_editInfo->Click += gcnew System::EventHandler(this, &MyForm::btn_editInfo_Click);
			// 
			// tb_currentPassword
			// 
			this->tb_currentPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_currentPassword->Location = System::Drawing::Point(575, 304);
			this->tb_currentPassword->Margin = System::Windows::Forms::Padding(4);
			this->tb_currentPassword->Name = L"tb_currentPassword";
			this->tb_currentPassword->ReadOnly = true;
			this->tb_currentPassword->Size = System::Drawing::Size(333, 42);
			this->tb_currentPassword->TabIndex = 7;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(280, 302);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(150, 41);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Password";
			// 
			// tb_currentPhoneNumber
			// 
			this->tb_currentPhoneNumber->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_currentPhoneNumber->Location = System::Drawing::Point(575, 167);
			this->tb_currentPhoneNumber->Margin = System::Windows::Forms::Padding(4);
			this->tb_currentPhoneNumber->Name = L"tb_currentPhoneNumber";
			this->tb_currentPhoneNumber->ReadOnly = true;
			this->tb_currentPhoneNumber->Size = System::Drawing::Size(333, 42);
			this->tb_currentPhoneNumber->TabIndex = 5;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(280, 164);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(230, 41);
			this->label7->TabIndex = 4;
			this->label7->Text = L"Phone Number";
			// 
			// tb_currentLocation
			// 
			this->tb_currentLocation->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_currentLocation->Location = System::Drawing::Point(575, 238);
			this->tb_currentLocation->Margin = System::Windows::Forms::Padding(4);
			this->tb_currentLocation->Name = L"tb_currentLocation";
			this->tb_currentLocation->ReadOnly = true;
			this->tb_currentLocation->Size = System::Drawing::Size(333, 42);
			this->tb_currentLocation->TabIndex = 3;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(280, 235);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(138, 41);
			this->label6->TabIndex = 2;
			this->label6->Text = L"Location";
			// 
			// tb_currentUsername
			// 
			this->tb_currentUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_currentUsername->Location = System::Drawing::Point(575, 103);
			this->tb_currentUsername->Margin = System::Windows::Forms::Padding(4);
			this->tb_currentUsername->Name = L"tb_currentUsername";
			this->tb_currentUsername->ReadOnly = true;
			this->tb_currentUsername->Size = System::Drawing::Size(333, 42);
			this->tb_currentUsername->TabIndex = 1;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(280, 97);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(164, 41);
			this->label5->TabIndex = 0;
			this->label5->Text = L"UserName";
			// 
			// pn_editInfo
			// 
			this->pn_editInfo->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_editInfo->Controls->Add(this->lb_errorLocation);
			this->pn_editInfo->Controls->Add(this->lb_errorPhone);
			this->pn_editInfo->Controls->Add(this->lb_errorUsername);
			this->pn_editInfo->Controls->Add(this->pictureBox11);
			this->pn_editInfo->Controls->Add(this->label15);
			this->pn_editInfo->Controls->Add(this->btn_cancelEdit);
			this->pn_editInfo->Controls->Add(this->btn_saveEdit);
			this->pn_editInfo->Controls->Add(this->tb_edit_phonenumber);
			this->pn_editInfo->Controls->Add(this->label9);
			this->pn_editInfo->Controls->Add(this->tb_edit_location);
			this->pn_editInfo->Controls->Add(this->label10);
			this->pn_editInfo->Controls->Add(this->tb_edit_username);
			this->pn_editInfo->Controls->Add(this->label11);
			this->pn_editInfo->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_editInfo->Location = System::Drawing::Point(0, 147);
			this->pn_editInfo->Margin = System::Windows::Forms::Padding(4);
			this->pn_editInfo->Name = L"pn_editInfo";
			this->pn_editInfo->Size = System::Drawing::Size(1189, 598);
			this->pn_editInfo->TabIndex = 2;
			// 
			// lb_errorLocation
			// 
			this->lb_errorLocation->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_errorLocation->ForeColor = System::Drawing::Color::Red;
			this->lb_errorLocation->Location = System::Drawing::Point(571, 363);
			this->lb_errorLocation->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb_errorLocation->Name = L"lb_errorLocation";
			this->lb_errorLocation->Size = System::Drawing::Size(484, 49);
			this->lb_errorLocation->TabIndex = 27;
			this->lb_errorLocation->Text = L"Error ";
			this->lb_errorLocation->Visible = false;
			// 
			// lb_errorPhone
			// 
			this->lb_errorPhone->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_errorPhone->ForeColor = System::Drawing::Color::Red;
			this->lb_errorPhone->Location = System::Drawing::Point(575, 268);
			this->lb_errorPhone->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb_errorPhone->Name = L"lb_errorPhone";
			this->lb_errorPhone->Size = System::Drawing::Size(480, 48);
			this->lb_errorPhone->TabIndex = 26;
			this->lb_errorPhone->Text = L"Error ";
			this->lb_errorPhone->Visible = false;
			// 
			// lb_errorUsername
			// 
			this->lb_errorUsername->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_errorUsername->ForeColor = System::Drawing::Color::Red;
			this->lb_errorUsername->Location = System::Drawing::Point(576, 175);
			this->lb_errorUsername->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb_errorUsername->Name = L"lb_errorUsername";
			this->lb_errorUsername->Size = System::Drawing::Size(479, 46);
			this->lb_errorUsername->TabIndex = 25;
			this->lb_errorUsername->Text = L"Error ";
			this->lb_errorUsername->Visible = false;
			// 
			// pictureBox11
			// 
			this->pictureBox11->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox11.Image")));
			this->pictureBox11->Location = System::Drawing::Point(329, 39);
			this->pictureBox11->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox11->Name = L"pictureBox11";
			this->pictureBox11->Size = System::Drawing::Size(51, 37);
			this->pictureBox11->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox11->TabIndex = 22;
			this->pictureBox11->TabStop = false;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(389, 37);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(379, 41);
			this->label15->TabIndex = 21;
			this->label15->Text = L"Edit Personal Information";
			// 
			// btn_cancelEdit
			// 
			this->btn_cancelEdit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_cancelEdit->FlatAppearance->BorderSize = 0;
			this->btn_cancelEdit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_cancelEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_cancelEdit->ForeColor = System::Drawing::Color::Black;
			this->btn_cancelEdit->Location = System::Drawing::Point(604, 427);
			this->btn_cancelEdit->Margin = System::Windows::Forms::Padding(4);
			this->btn_cancelEdit->Name = L"btn_cancelEdit";
			this->btn_cancelEdit->Size = System::Drawing::Size(145, 66);
			this->btn_cancelEdit->TabIndex = 13;
			this->btn_cancelEdit->Text = L"Cancel";
			this->btn_cancelEdit->UseVisualStyleBackColor = false;
			this->btn_cancelEdit->Click += gcnew System::EventHandler(this, &MyForm::btn_cancelEdit_Click);
			// 
			// btn_saveEdit
			// 
			this->btn_saveEdit->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->btn_saveEdit->FlatAppearance->BorderSize = 3;
			this->btn_saveEdit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_saveEdit->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_saveEdit->Location = System::Drawing::Point(440, 427);
			this->btn_saveEdit->Margin = System::Windows::Forms::Padding(4);
			this->btn_saveEdit->Name = L"btn_saveEdit";
			this->btn_saveEdit->Size = System::Drawing::Size(131, 66);
			this->btn_saveEdit->TabIndex = 12;
			this->btn_saveEdit->Text = L"Save";
			this->btn_saveEdit->UseVisualStyleBackColor = true;
			this->btn_saveEdit->Click += gcnew System::EventHandler(this, &MyForm::btn_saveEdit_Click);
			// 
			// tb_edit_phonenumber
			// 
			this->tb_edit_phonenumber->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_edit_phonenumber->Location = System::Drawing::Point(575, 219);
			this->tb_edit_phonenumber->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_phonenumber->Name = L"tb_edit_phonenumber";
			this->tb_edit_phonenumber->Size = System::Drawing::Size(333, 42);
			this->tb_edit_phonenumber->TabIndex = 11;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(280, 215);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(230, 41);
			this->label9->TabIndex = 10;
			this->label9->Text = L"Phone Number";
			// 
			// tb_edit_location
			// 
			this->tb_edit_location->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_edit_location->Location = System::Drawing::Point(575, 316);
			this->tb_edit_location->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_location->Name = L"tb_edit_location";
			this->tb_edit_location->Size = System::Drawing::Size(333, 42);
			this->tb_edit_location->TabIndex = 9;
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(280, 314);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(138, 41);
			this->label10->TabIndex = 8;
			this->label10->Text = L"Location";
			// 
			// tb_edit_username
			// 
			this->tb_edit_username->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_edit_username->Location = System::Drawing::Point(575, 130);
			this->tb_edit_username->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_username->Name = L"tb_edit_username";
			this->tb_edit_username->Size = System::Drawing::Size(333, 42);
			this->tb_edit_username->TabIndex = 7;
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(280, 124);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(164, 41);
			this->label11->TabIndex = 6;
			this->label11->Text = L"UserName";
			// 
			// pn_resetPassword
			// 
			this->pn_resetPassword->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_resetPassword->Controls->Add(this->lb_newpassword);
			this->pn_resetPassword->Controls->Add(this->pictureBox12);
			this->pn_resetPassword->Controls->Add(this->tb_confirmPassword);
			this->pn_resetPassword->Controls->Add(this->label17);
			this->pn_resetPassword->Controls->Add(this->label14);
			this->pn_resetPassword->Controls->Add(this->button2);
			this->pn_resetPassword->Controls->Add(this->btn_saveResetPassword);
			this->pn_resetPassword->Controls->Add(this->textBox8);
			this->pn_resetPassword->Controls->Add(this->label12);
			this->pn_resetPassword->Controls->Add(this->tb_newPassword);
			this->pn_resetPassword->Controls->Add(this->label13);
			this->pn_resetPassword->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_resetPassword->Location = System::Drawing::Point(0, 147);
			this->pn_resetPassword->Margin = System::Windows::Forms::Padding(4);
			this->pn_resetPassword->Name = L"pn_resetPassword";
			this->pn_resetPassword->Size = System::Drawing::Size(1189, 598);
			this->pn_resetPassword->TabIndex = 2;
			// 
			// lb_newpassword
			// 
			this->lb_newpassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_newpassword->ForeColor = System::Drawing::Color::Red;
			this->lb_newpassword->Location = System::Drawing::Point(273, 316);
			this->lb_newpassword->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lb_newpassword->Name = L"lb_newpassword";
			this->lb_newpassword->Size = System::Drawing::Size(681, 28);
			this->lb_newpassword->TabIndex = 24;
			this->lb_newpassword->Text = L"Error ";
			this->lb_newpassword->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lb_newpassword->Visible = false;
			// 
			// pictureBox12
			// 
			this->pictureBox12->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox12.Image")));
			this->pictureBox12->Location = System::Drawing::Point(409, 30);
			this->pictureBox12->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox12->Name = L"pictureBox12";
			this->pictureBox12->Size = System::Drawing::Size(51, 37);
			this->pictureBox12->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox12->TabIndex = 23;
			this->pictureBox12->TabStop = false;
			// 
			// tb_confirmPassword
			// 
			this->tb_confirmPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_confirmPassword->Location = System::Drawing::Point(587, 241);
			this->tb_confirmPassword->Margin = System::Windows::Forms::Padding(4);
			this->tb_confirmPassword->Name = L"tb_confirmPassword";
			this->tb_confirmPassword->PasswordChar = '*';
			this->tb_confirmPassword->Size = System::Drawing::Size(333, 42);
			this->tb_confirmPassword->TabIndex = 22;
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(269, 246);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(273, 41);
			this->label17->TabIndex = 21;
			this->label17->Text = L"Confirm Password";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(468, 25);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(234, 41);
			this->label14->TabIndex = 20;
			this->label14->Text = L"Reset Password";
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ForeColor = System::Drawing::Color::Black;
			this->button2->Location = System::Drawing::Point(604, 384);
			this->button2->Margin = System::Windows::Forms::Padding(4);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(145, 66);
			this->button2->TabIndex = 19;
			this->button2->Text = L"Cancel";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// btn_saveResetPassword
			// 
			this->btn_saveResetPassword->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->btn_saveResetPassword->FlatAppearance->BorderSize = 3;
			this->btn_saveResetPassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_saveResetPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_saveResetPassword->Location = System::Drawing::Point(440, 384);
			this->btn_saveResetPassword->Margin = System::Windows::Forms::Padding(4);
			this->btn_saveResetPassword->Name = L"btn_saveResetPassword";
			this->btn_saveResetPassword->Size = System::Drawing::Size(131, 66);
			this->btn_saveResetPassword->TabIndex = 18;
			this->btn_saveResetPassword->Text = L"Save";
			this->btn_saveResetPassword->UseVisualStyleBackColor = true;
			this->btn_saveResetPassword->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// textBox8
			// 
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->textBox8->Location = System::Drawing::Point(585, 107);
			this->textBox8->Margin = System::Windows::Forms::Padding(4);
			this->textBox8->Name = L"textBox8";
			this->textBox8->ReadOnly = true;
			this->textBox8->Size = System::Drawing::Size(333, 42);
			this->textBox8->TabIndex = 17;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(281, 112);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(265, 41);
			this->label12->TabIndex = 16;
			this->label12->Text = L"Current Password";
			// 
			// tb_newPassword
			// 
			this->tb_newPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_newPassword->Location = System::Drawing::Point(585, 177);
			this->tb_newPassword->Margin = System::Windows::Forms::Padding(4);
			this->tb_newPassword->Name = L"tb_newPassword";
			this->tb_newPassword->PasswordChar = '*';
			this->tb_newPassword->Size = System::Drawing::Size(333, 42);
			this->tb_newPassword->TabIndex = 15;
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(307, 181);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(222, 41);
			this->label13->TabIndex = 14;
			this->label13->Text = L"New Password";
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->label1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1189, 147);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Edit Your Information";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pn_blank
			// 
			this->pn_blank->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_blank->Controls->Add(this->pb_blankpicutre);
			this->pn_blank->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_blank->Location = System::Drawing::Point(296, 0);
			this->pn_blank->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_blank->Name = L"pn_blank";
			this->pn_blank->Size = System::Drawing::Size(1189, 745);
			this->pn_blank->TabIndex = 4;
			// 
			// pb_blankpicutre
			// 
			this->pb_blankpicutre->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pb_blankpicutre->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pb_blankpicutre->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_blankpicutre.Image")));
			this->pb_blankpicutre->Location = System::Drawing::Point(0, 0);
			this->pb_blankpicutre->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pb_blankpicutre->Name = L"pb_blankpicutre";
			this->pb_blankpicutre->Size = System::Drawing::Size(1189, 745);
			this->pb_blankpicutre->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb_blankpicutre->TabIndex = 2;
			this->pb_blankpicutre->TabStop = false;
			// 
			// pn_products
			// 
			this->pn_products->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)));
			this->pn_products->Controls->Add(this->pn_main_category);
			this->pn_products->Controls->Add(this->pn_pet_supplies_category);
			this->pn_products->Controls->Add(this->pn_household_category);
			this->pn_products->Controls->Add(this->pn_snacks_category);
			this->pn_products->Controls->Add(this->pn_bakery_category);
			this->pn_products->Controls->Add(this->pn_poultry_category);
			this->pn_products->Controls->Add(this->pn_seafood_category);
			this->pn_products->Controls->Add(this->pn_butchershop_category);
			this->pn_products->Controls->Add(this->pn_dairy_category);
			this->pn_products->Controls->Add(this->pn_vegetable_category);
			this->pn_products->Controls->Add(this->pn_fruits_category);
			this->pn_products->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_products->Location = System::Drawing::Point(296, 0);
			this->pn_products->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_products->Name = L"pn_products";
			this->pn_products->Size = System::Drawing::Size(1189, 745);
			this->pn_products->TabIndex = 2;
			// 
			// pn_main_category
			// 
			this->pn_main_category->Controls->Add(this->label2);
			this->pn_main_category->Controls->Add(this->flowLayoutPanel2);
			this->pn_main_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_category->Location = System::Drawing::Point(0, 0);
			this->pn_main_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_main_category->Name = L"pn_main_category";
			this->pn_main_category->Size = System::Drawing::Size(1189, 745);
			this->pn_main_category->TabIndex = 14;
			// 
			// label2
			// 
			this->label2->Dock = System::Windows::Forms::DockStyle::Top;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(0, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(1189, 148);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Products";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->AutoScroll = true;
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->flowLayoutPanel2->Controls->Add(this->btn_fruits);
			this->flowLayoutPanel2->Controls->Add(this->btn_vegetabe);
			this->flowLayoutPanel2->Controls->Add(this->btn_dairy);
			this->flowLayoutPanel2->Controls->Add(this->btn_butcher);
			this->flowLayoutPanel2->Controls->Add(this->btn_seafood);
			this->flowLayoutPanel2->Controls->Add(this->btn_poultry);
			this->flowLayoutPanel2->Controls->Add(this->btn_bakery);
			this->flowLayoutPanel2->Controls->Add(this->btn_snacks);
			this->flowLayoutPanel2->Controls->Add(this->btn_household);
			this->flowLayoutPanel2->Controls->Add(this->btn_pet);
			this->flowLayoutPanel2->Location = System::Drawing::Point(-7, 148);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Padding = System::Windows::Forms::Padding(13, 0, 0, 0);
			this->flowLayoutPanel2->Size = System::Drawing::Size(1193, 597);
			this->flowLayoutPanel2->TabIndex = 0;
			// 
			// btn_fruits
			// 
			this->btn_fruits->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->btn_fruits->FlatAppearance->BorderSize = 0;
			this->btn_fruits->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_fruits->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_fruits->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_fruits.Image")));
			this->btn_fruits->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_fruits->Location = System::Drawing::Point(20, 7);
			this->btn_fruits->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_fruits->Name = L"btn_fruits";
			this->btn_fruits->Size = System::Drawing::Size(560, 135);
			this->btn_fruits->TabIndex = 0;
			this->btn_fruits->Text = L"Fresh Fruits";
			this->btn_fruits->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_fruits->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_fruits->UseCompatibleTextRendering = true;
			this->btn_fruits->UseMnemonic = false;
			this->btn_fruits->UseVisualStyleBackColor = false;
			this->btn_fruits->Click += gcnew System::EventHandler(this, &MyForm::btn_fruits_Click);
			// 
			// btn_vegetabe
			// 
			this->btn_vegetabe->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_vegetabe->FlatAppearance->BorderSize = 0;
			this->btn_vegetabe->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_vegetabe->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_vegetabe->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_vegetabe.Image")));
			this->btn_vegetabe->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_vegetabe->Location = System::Drawing::Point(592, 7);
			this->btn_vegetabe->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_vegetabe->Name = L"btn_vegetabe";
			this->btn_vegetabe->Size = System::Drawing::Size(560, 135);
			this->btn_vegetabe->TabIndex = 1;
			this->btn_vegetabe->Text = L"Fresh Vegetables";
			this->btn_vegetabe->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_vegetabe->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_vegetabe->UseCompatibleTextRendering = true;
			this->btn_vegetabe->UseVisualStyleBackColor = false;
			this->btn_vegetabe->Click += gcnew System::EventHandler(this, &MyForm::btn_vegetabe_Click);
			// 
			// btn_dairy
			// 
			this->btn_dairy->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_dairy->FlatAppearance->BorderSize = 0;
			this->btn_dairy->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_dairy->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_dairy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_dairy.Image")));
			this->btn_dairy->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_dairy->Location = System::Drawing::Point(20, 154);
			this->btn_dairy->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_dairy->Name = L"btn_dairy";
			this->btn_dairy->Size = System::Drawing::Size(560, 135);
			this->btn_dairy->TabIndex = 2;
			this->btn_dairy->Text = L"Dairy and Eggs";
			this->btn_dairy->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_dairy->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_dairy->UseCompatibleTextRendering = true;
			this->btn_dairy->UseVisualStyleBackColor = false;
			this->btn_dairy->Click += gcnew System::EventHandler(this, &MyForm::btn_dairy_Click);
			// 
			// btn_butcher
			// 
			this->btn_butcher->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->btn_butcher->FlatAppearance->BorderSize = 0;
			this->btn_butcher->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_butcher->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_butcher->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_butcher.Image")));
			this->btn_butcher->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_butcher->Location = System::Drawing::Point(592, 154);
			this->btn_butcher->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_butcher->Name = L"btn_butcher";
			this->btn_butcher->Size = System::Drawing::Size(560, 135);
			this->btn_butcher->TabIndex = 3;
			this->btn_butcher->Text = L"Bucher shop";
			this->btn_butcher->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_butcher->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_butcher->UseCompatibleTextRendering = true;
			this->btn_butcher->UseVisualStyleBackColor = false;
			this->btn_butcher->Click += gcnew System::EventHandler(this, &MyForm::btn_butcher_Click);
			// 
			// btn_seafood
			// 
			this->btn_seafood->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->btn_seafood->FlatAppearance->BorderSize = 0;
			this->btn_seafood->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_seafood->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_seafood->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seafood.Image")));
			this->btn_seafood->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_seafood->Location = System::Drawing::Point(20, 301);
			this->btn_seafood->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_seafood->Name = L"btn_seafood";
			this->btn_seafood->Size = System::Drawing::Size(560, 135);
			this->btn_seafood->TabIndex = 4;
			this->btn_seafood->Text = L"Seafood";
			this->btn_seafood->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_seafood->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_seafood->UseCompatibleTextRendering = true;
			this->btn_seafood->UseVisualStyleBackColor = false;
			this->btn_seafood->Click += gcnew System::EventHandler(this, &MyForm::btn_seafood_Click);
			// 
			// btn_poultry
			// 
			this->btn_poultry->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_poultry->FlatAppearance->BorderSize = 0;
			this->btn_poultry->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_poultry->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_poultry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_poultry.Image")));
			this->btn_poultry->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_poultry->Location = System::Drawing::Point(592, 301);
			this->btn_poultry->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_poultry->Name = L"btn_poultry";
			this->btn_poultry->Size = System::Drawing::Size(560, 135);
			this->btn_poultry->TabIndex = 5;
			this->btn_poultry->Text = L"Poultry";
			this->btn_poultry->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_poultry->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_poultry->UseCompatibleTextRendering = true;
			this->btn_poultry->UseVisualStyleBackColor = false;
			this->btn_poultry->Click += gcnew System::EventHandler(this, &MyForm::btn_poultry_Click);
			// 
			// btn_bakery
			// 
			this->btn_bakery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_bakery->FlatAppearance->BorderSize = 0;
			this->btn_bakery->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_bakery->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_bakery->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_bakery.Image")));
			this->btn_bakery->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_bakery->Location = System::Drawing::Point(20, 448);
			this->btn_bakery->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_bakery->Name = L"btn_bakery";
			this->btn_bakery->Size = System::Drawing::Size(560, 135);
			this->btn_bakery->TabIndex = 6;
			this->btn_bakery->Text = L"Bakery and Bread";
			this->btn_bakery->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_bakery->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_bakery->UseCompatibleTextRendering = true;
			this->btn_bakery->UseVisualStyleBackColor = false;
			this->btn_bakery->Click += gcnew System::EventHandler(this, &MyForm::btn_bakery_Click);
			// 
			// btn_snacks
			// 
			this->btn_snacks->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->btn_snacks->FlatAppearance->BorderSize = 0;
			this->btn_snacks->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_snacks->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_snacks->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_snacks.Image")));
			this->btn_snacks->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_snacks->Location = System::Drawing::Point(592, 448);
			this->btn_snacks->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_snacks->Name = L"btn_snacks";
			this->btn_snacks->Size = System::Drawing::Size(560, 135);
			this->btn_snacks->TabIndex = 7;
			this->btn_snacks->Text = L"Snacks and Sweets";
			this->btn_snacks->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_snacks->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_snacks->UseCompatibleTextRendering = true;
			this->btn_snacks->UseVisualStyleBackColor = false;
			this->btn_snacks->Click += gcnew System::EventHandler(this, &MyForm::btn_snacks_Click);
			// 
			// btn_household
			// 
			this->btn_household->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(160)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->btn_household->FlatAppearance->BorderSize = 0;
			this->btn_household->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_household->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_household->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_household.Image")));
			this->btn_household->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_household->Location = System::Drawing::Point(20, 595);
			this->btn_household->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_household->Name = L"btn_household";
			this->btn_household->Size = System::Drawing::Size(560, 135);
			this->btn_household->TabIndex = 8;
			this->btn_household->Text = L"Household and Cleaning supplies";
			this->btn_household->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_household->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_household->UseCompatibleTextRendering = true;
			this->btn_household->UseVisualStyleBackColor = false;
			this->btn_household->Click += gcnew System::EventHandler(this, &MyForm::btn_household_Click);
			// 
			// btn_pet
			// 
			this->btn_pet->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_pet->FlatAppearance->BorderSize = 0;
			this->btn_pet->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_pet->ForeColor = System::Drawing::Color::WhiteSmoke;
			this->btn_pet->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_pet.Image")));
			this->btn_pet->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_pet->Location = System::Drawing::Point(592, 595);
			this->btn_pet->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_pet->Name = L"btn_pet";
			this->btn_pet->Size = System::Drawing::Size(560, 135);
			this->btn_pet->TabIndex = 9;
			this->btn_pet->Text = L"Pet Supplies";
			this->btn_pet->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_pet->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			this->btn_pet->UseCompatibleTextRendering = true;
			this->btn_pet->UseVisualStyleBackColor = false;
			this->btn_pet->Click += gcnew System::EventHandler(this, &MyForm::btn_pet_Click);
			// 
			// pn_pet_supplies_category
			// 
			this->pn_pet_supplies_category->Controls->Add(this->flowLayoutPanel12);
			this->pn_pet_supplies_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_pet_supplies_category->Location = System::Drawing::Point(0, 0);
			this->pn_pet_supplies_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_pet_supplies_category->Name = L"pn_pet_supplies_category";
			this->pn_pet_supplies_category->Size = System::Drawing::Size(1189, 745);
			this->pn_pet_supplies_category->TabIndex = 6;
			// 
			// flowLayoutPanel12
			// 
			this->flowLayoutPanel12->AutoScroll = true;
			this->flowLayoutPanel12->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel12->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel12->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel12->Name = L"flowLayoutPanel12";
			this->flowLayoutPanel12->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel12->TabIndex = 0;
			// 
			// pn_household_category
			// 
			this->pn_household_category->Controls->Add(this->flowLayoutPanel11);
			this->pn_household_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_household_category->Location = System::Drawing::Point(0, 0);
			this->pn_household_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_household_category->Name = L"pn_household_category";
			this->pn_household_category->Size = System::Drawing::Size(1189, 745);
			this->pn_household_category->TabIndex = 17;
			// 
			// flowLayoutPanel11
			// 
			this->flowLayoutPanel11->AutoScroll = true;
			this->flowLayoutPanel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel11->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel11->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel11->Name = L"flowLayoutPanel11";
			this->flowLayoutPanel11->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel11->TabIndex = 0;
			// 
			// pn_snacks_category
			// 
			this->pn_snacks_category->Controls->Add(this->flowLayoutPanel10);
			this->pn_snacks_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_snacks_category->Location = System::Drawing::Point(0, 0);
			this->pn_snacks_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_snacks_category->Name = L"pn_snacks_category";
			this->pn_snacks_category->Size = System::Drawing::Size(1189, 745);
			this->pn_snacks_category->TabIndex = 16;
			// 
			// flowLayoutPanel10
			// 
			this->flowLayoutPanel10->AutoScroll = true;
			this->flowLayoutPanel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel10->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel10->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel10->Name = L"flowLayoutPanel10";
			this->flowLayoutPanel10->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel10->TabIndex = 0;
			// 
			// pn_bakery_category
			// 
			this->pn_bakery_category->Controls->Add(this->flowLayoutPanel9);
			this->pn_bakery_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_bakery_category->Location = System::Drawing::Point(0, 0);
			this->pn_bakery_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_bakery_category->Name = L"pn_bakery_category";
			this->pn_bakery_category->Size = System::Drawing::Size(1189, 745);
			this->pn_bakery_category->TabIndex = 18;
			// 
			// flowLayoutPanel9
			// 
			this->flowLayoutPanel9->AutoScroll = true;
			this->flowLayoutPanel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel9->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel9->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel9->Name = L"flowLayoutPanel9";
			this->flowLayoutPanel9->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel9->TabIndex = 0;
			// 
			// pn_poultry_category
			// 
			this->pn_poultry_category->Controls->Add(this->flowLayoutPanel8);
			this->pn_poultry_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_poultry_category->Location = System::Drawing::Point(0, 0);
			this->pn_poultry_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_poultry_category->Name = L"pn_poultry_category";
			this->pn_poultry_category->Size = System::Drawing::Size(1189, 745);
			this->pn_poultry_category->TabIndex = 15;
			// 
			// flowLayoutPanel8
			// 
			this->flowLayoutPanel8->AutoScroll = true;
			this->flowLayoutPanel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel8->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel8->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel8->Name = L"flowLayoutPanel8";
			this->flowLayoutPanel8->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel8->TabIndex = 0;
			// 
			// pn_seafood_category
			// 
			this->pn_seafood_category->Controls->Add(this->flowLayoutPanel7);
			this->pn_seafood_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_seafood_category->Location = System::Drawing::Point(0, 0);
			this->pn_seafood_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_seafood_category->Name = L"pn_seafood_category";
			this->pn_seafood_category->Size = System::Drawing::Size(1189, 745);
			this->pn_seafood_category->TabIndex = 7;
			// 
			// flowLayoutPanel7
			// 
			this->flowLayoutPanel7->AutoScroll = true;
			this->flowLayoutPanel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel7->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel7->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel7->Name = L"flowLayoutPanel7";
			this->flowLayoutPanel7->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel7->TabIndex = 0;
			// 
			// pn_butchershop_category
			// 
			this->pn_butchershop_category->Controls->Add(this->flowLayoutPanel6);
			this->pn_butchershop_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_butchershop_category->Location = System::Drawing::Point(0, 0);
			this->pn_butchershop_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_butchershop_category->Name = L"pn_butchershop_category";
			this->pn_butchershop_category->Size = System::Drawing::Size(1189, 745);
			this->pn_butchershop_category->TabIndex = 8;
			// 
			// flowLayoutPanel6
			// 
			this->flowLayoutPanel6->AutoScroll = true;
			this->flowLayoutPanel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel6->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel6->Name = L"flowLayoutPanel6";
			this->flowLayoutPanel6->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel6->TabIndex = 0;
			// 
			// pn_dairy_category
			// 
			this->pn_dairy_category->Controls->Add(this->flowLayoutPanel5);
			this->pn_dairy_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_dairy_category->Location = System::Drawing::Point(0, 0);
			this->pn_dairy_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_dairy_category->Name = L"pn_dairy_category";
			this->pn_dairy_category->Size = System::Drawing::Size(1189, 745);
			this->pn_dairy_category->TabIndex = 5;
			// 
			// flowLayoutPanel5
			// 
			this->flowLayoutPanel5->AutoScroll = true;
			this->flowLayoutPanel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel5->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel5->Name = L"flowLayoutPanel5";
			this->flowLayoutPanel5->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel5->TabIndex = 0;
			// 
			// pn_vegetable_category
			// 
			this->pn_vegetable_category->Controls->Add(this->flowLayoutPanel4);
			this->pn_vegetable_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_vegetable_category->Location = System::Drawing::Point(0, 0);
			this->pn_vegetable_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_vegetable_category->Name = L"pn_vegetable_category";
			this->pn_vegetable_category->Size = System::Drawing::Size(1189, 745);
			this->pn_vegetable_category->TabIndex = 19;
			// 
			// flowLayoutPanel4
			// 
			this->flowLayoutPanel4->AutoScroll = true;
			this->flowLayoutPanel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel4->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel4->Name = L"flowLayoutPanel4";
			this->flowLayoutPanel4->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel4->TabIndex = 0;
			// 
			// pn_fruits_category
			// 
			this->pn_fruits_category->Controls->Add(this->flowLayoutPanel3);
			this->pn_fruits_category->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_fruits_category->Location = System::Drawing::Point(0, 0);
			this->pn_fruits_category->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_fruits_category->Name = L"pn_fruits_category";
			this->pn_fruits_category->Size = System::Drawing::Size(1189, 745);
			this->pn_fruits_category->TabIndex = 20;
			// 
			// flowLayoutPanel3
			// 
			this->flowLayoutPanel3->AutoScroll = true;
			this->flowLayoutPanel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel3->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel3->Name = L"flowLayoutPanel3";
			this->flowLayoutPanel3->Size = System::Drawing::Size(1189, 745);
			this->flowLayoutPanel3->TabIndex = 0;
			// 
			// pn_orders
			// 
			this->pn_orders->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)));
			this->pn_orders->Controls->Add(this->label19);
			this->pn_orders->Controls->Add(this->orderList);
			this->pn_orders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_orders->Location = System::Drawing::Point(296, 0);
			this->pn_orders->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_orders->Name = L"pn_orders";
			this->pn_orders->Size = System::Drawing::Size(1189, 745);
			this->pn_orders->TabIndex = 3;
			// 
			// label19
			// 
			this->label19->Dock = System::Windows::Forms::DockStyle::Top;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label19->Location = System::Drawing::Point(0, 0);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(1189, 148);
			this->label19->TabIndex = 2;
			this->label19->Text = L"Order";
			this->label19->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// orderList
			// 
			this->orderList->AutoScroll = true;
			this->orderList->Location = System::Drawing::Point(0, 148);
			this->orderList->Margin = System::Windows::Forms::Padding(4);
			this->orderList->Name = L"orderList";
			this->orderList->Size = System::Drawing::Size(1189, 597);
			this->orderList->TabIndex = 3;
			// 
			// pn_viewBill
			// 
			this->pn_viewBill->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_viewBill->Controls->Add(this->pb_theinvoice);
			this->pn_viewBill->Controls->Add(this->pn);
			this->pn_viewBill->Controls->Add(this->lb_theinvoice);
			this->pn_viewBill->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_viewBill->Location = System::Drawing::Point(296, 0);
			this->pn_viewBill->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_viewBill->Name = L"pn_viewBill";
			this->pn_viewBill->Size = System::Drawing::Size(1189, 745);
			this->pn_viewBill->TabIndex = 5;
			// 
			// pb_theinvoice
			// 
			this->pb_theinvoice->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_theinvoice.BackgroundImage")));
			this->pb_theinvoice->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pb_theinvoice->Location = System::Drawing::Point(957, 15);
			this->pb_theinvoice->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pb_theinvoice->Name = L"pb_theinvoice";
			this->pb_theinvoice->Size = System::Drawing::Size(203, 101);
			this->pb_theinvoice->TabIndex = 3;
			this->pb_theinvoice->TabStop = false;
			// 
			// pn
			// 
			this->pn->Controls->Add(this->btn_print);
			this->pn->Controls->Add(this->flowLayoutPanel13);
			this->pn->Controls->Add(this->tb_customername_theincoive);
			this->pn->Controls->Add(this->lb_customername_theinvoice);
			this->pn->Controls->Add(this->tb_date_theinvoice);
			this->pn->Controls->Add(this->tb_invoicenumber_theinvoice);
			this->pn->Controls->Add(this->lb_date_theinvice);
			this->pn->Controls->Add(this->lb_invoicenumber_theinvoice);
			this->pn->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn->Location = System::Drawing::Point(0, 127);
			this->pn->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn->Name = L"pn";
			this->pn->Size = System::Drawing::Size(1189, 618);
			this->pn->TabIndex = 2;
			// 
			// btn_print
			// 
			this->btn_print->BackColor = System::Drawing::Color::Purple;
			this->btn_print->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_print->ForeColor = System::Drawing::Color::Yellow;
			this->btn_print->Location = System::Drawing::Point(927, 50);
			this->btn_print->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_print->Name = L"btn_print";
			this->btn_print->Size = System::Drawing::Size(235, 62);
			this->btn_print->TabIndex = 9;
			this->btn_print->Text = L"Print";
			this->btn_print->UseVisualStyleBackColor = false;
			this->btn_print->Click += gcnew System::EventHandler(this, &MyForm::btn_print_Click);
			// 
			// flowLayoutPanel13
			// 
			this->flowLayoutPanel13->AutoScroll = true;
			this->flowLayoutPanel13->Controls->Add(this->dataGridView1);
			this->flowLayoutPanel13->Controls->Add(this->panel2);
			this->flowLayoutPanel13->Location = System::Drawing::Point(9, 155);
			this->flowLayoutPanel13->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel13->Name = L"flowLayoutPanel13";
			this->flowLayoutPanel13->Size = System::Drawing::Size(1176, 428);
			this->flowLayoutPanel13->TabIndex = 8;
			// 
			// dataGridView1
			// 
			this->dataGridView1->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridView1->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {
				this->colproduct,
					this->colquantity, this->colunitprice, this->colsubtotal
			});
			this->dataGridView1->Location = System::Drawing::Point(3, 2);
			this->dataGridView1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->dataGridView1->Name = L"dataGridView1";
			this->dataGridView1->RowHeadersWidth = 51;
			this->dataGridView1->RowTemplate->Height = 24;
			this->dataGridView1->Size = System::Drawing::Size(1149, 256);
			this->dataGridView1->TabIndex = 7;
			// 
			// colproduct
			// 
			this->colproduct->HeaderText = L"Product";
			this->colproduct->MinimumWidth = 6;
			this->colproduct->Name = L"colproduct";
			// 
			// colquantity
			// 
			this->colquantity->HeaderText = L"Quantity";
			this->colquantity->MinimumWidth = 6;
			this->colquantity->Name = L"colquantity";
			// 
			// colunitprice
			// 
			this->colunitprice->HeaderText = L"Unit price";
			this->colunitprice->MinimumWidth = 6;
			this->colunitprice->Name = L"colunitprice";
			// 
			// colsubtotal
			// 
			this->colsubtotal->HeaderText = L"Subtotal";
			this->colsubtotal->MinimumWidth = 6;
			this->colsubtotal->Name = L"colsubtotal";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->lb_total_number);
			this->panel2->Controls->Add(this->lb_shipping_number);
			this->panel2->Controls->Add(this->lb_vat_number);
			this->panel2->Controls->Add(this->lb_discount_number);
			this->panel2->Controls->Add(this->lb_shipping);
			this->panel2->Controls->Add(this->lb_vat);
			this->panel2->Controls->Add(this->lb_discount);
			this->panel2->Controls->Add(this->lb_total);
			this->panel2->Controls->Add(this->label22);
			this->panel2->Controls->Add(this->lb_beforevat_number);
			this->panel2->Controls->Add(this->lb_beforevat);
			this->panel2->Location = System::Drawing::Point(3, 262);
			this->panel2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1137, 164);
			this->panel2->TabIndex = 8;
			// 
			// lb_total_number
			// 
			this->lb_total_number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_total_number->ForeColor = System::Drawing::Color::Purple;
			this->lb_total_number->Location = System::Drawing::Point(780, 62);
			this->lb_total_number->Name = L"lb_total_number";
			this->lb_total_number->Size = System::Drawing::Size(353, 50);
			this->lb_total_number->TabIndex = 10;
			// 
			// lb_shipping_number
			// 
			this->lb_shipping_number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_shipping_number->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_shipping_number->Location = System::Drawing::Point(300, 102);
			this->lb_shipping_number->Name = L"lb_shipping_number";
			this->lb_shipping_number->Size = System::Drawing::Size(161, 37);
			this->lb_shipping_number->TabIndex = 9;
			// 
			// lb_vat_number
			// 
			this->lb_vat_number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_vat_number->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_vat_number->Location = System::Drawing::Point(300, 68);
			this->lb_vat_number->Name = L"lb_vat_number";
			this->lb_vat_number->Size = System::Drawing::Size(161, 37);
			this->lb_vat_number->TabIndex = 8;
			// 
			// lb_discount_number
			// 
			this->lb_discount_number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_discount_number->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_discount_number->Location = System::Drawing::Point(300, 34);
			this->lb_discount_number->Name = L"lb_discount_number";
			this->lb_discount_number->Size = System::Drawing::Size(161, 37);
			this->lb_discount_number->TabIndex = 7;
			// 
			// lb_shipping
			// 
			this->lb_shipping->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_shipping->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_shipping->Location = System::Drawing::Point(4, 105);
			this->lb_shipping->Name = L"lb_shipping";
			this->lb_shipping->Size = System::Drawing::Size(284, 34);
			this->lb_shipping->TabIndex = 6;
			this->lb_shipping->Text = L"Shipping Cost:  ";
			// 
			// lb_vat
			// 
			this->lb_vat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_vat->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_vat->Location = System::Drawing::Point(4, 71);
			this->lb_vat->Name = L"lb_vat";
			this->lb_vat->Size = System::Drawing::Size(268, 34);
			this->lb_vat->TabIndex = 5;
			this->lb_vat->Text = L"VAT(14%): ";
			// 
			// lb_discount
			// 
			this->lb_discount->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_discount->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_discount->Location = System::Drawing::Point(4, 37);
			this->lb_discount->Name = L"lb_discount";
			this->lb_discount->Size = System::Drawing::Size(284, 34);
			this->lb_discount->TabIndex = 4;
			this->lb_discount->Text = L"Discount Applied:  ";
			// 
			// lb_total
			// 
			this->lb_total->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_total->ForeColor = System::Drawing::Color::Purple;
			this->lb_total->Location = System::Drawing::Point(569, 62);
			this->lb_total->Name = L"lb_total";
			this->lb_total->Size = System::Drawing::Size(257, 44);
			this->lb_total->TabIndex = 3;
			this->lb_total->Text = L"Total (After VAT):   ";
			// 
			// label22
			// 
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label22->ForeColor = System::Drawing::Color::Purple;
			this->label22->Location = System::Drawing::Point(203, 81);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(273, 44);
			this->label22->TabIndex = 2;
			// 
			// lb_beforevat_number
			// 
			this->lb_beforevat_number->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_beforevat_number->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(64)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_beforevat_number->Location = System::Drawing::Point(300, 2);
			this->lb_beforevat_number->Name = L"lb_beforevat_number";
			this->lb_beforevat_number->Size = System::Drawing::Size(161, 37);
			this->lb_beforevat_number->TabIndex = 1;
			// 
			// lb_beforevat
			// 
			this->lb_beforevat->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_beforevat->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(64)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_beforevat->Location = System::Drawing::Point(3, 6);
			this->lb_beforevat->Name = L"lb_beforevat";
			this->lb_beforevat->Size = System::Drawing::Size(297, 34);
			this->lb_beforevat->TabIndex = 0;
			this->lb_beforevat->Text = L"Total(Before VAT): ";
			// 
			// tb_customername_theincoive
			// 
			this->tb_customername_theincoive->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tb_customername_theincoive->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->tb_customername_theincoive->Location = System::Drawing::Point(227, 100);
			this->tb_customername_theincoive->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_customername_theincoive->Name = L"tb_customername_theincoive";
			this->tb_customername_theincoive->Size = System::Drawing::Size(611, 30);
			this->tb_customername_theincoive->TabIndex = 5;
			this->tb_customername_theincoive->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tb_customername_theincoive->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_customername_theincoive_KeyPress);
			// 
			// lb_customername_theinvoice
			// 
			this->lb_customername_theinvoice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_customername_theinvoice->Location = System::Drawing::Point(3, 100);
			this->lb_customername_theinvoice->Name = L"lb_customername_theinvoice";
			this->lb_customername_theinvoice->Size = System::Drawing::Size(236, 42);
			this->lb_customername_theinvoice->TabIndex = 4;
			this->lb_customername_theinvoice->Text = L"Customer name:";
			// 
			// tb_date_theinvoice
			// 
			this->tb_date_theinvoice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_date_theinvoice->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->tb_date_theinvoice->Location = System::Drawing::Point(227, 50);
			this->tb_date_theinvoice->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_date_theinvoice->Name = L"tb_date_theinvoice";
			this->tb_date_theinvoice->Size = System::Drawing::Size(611, 30);
			this->tb_date_theinvoice->TabIndex = 3;
			this->tb_date_theinvoice->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tb_date_theinvoice->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_date_theinvoice_KeyPress);
			// 
			// tb_invoicenumber_theinvoice
			// 
			this->tb_invoicenumber_theinvoice->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->tb_invoicenumber_theinvoice->ForeColor = System::Drawing::Color::Red;
			this->tb_invoicenumber_theinvoice->Location = System::Drawing::Point(227, 7);
			this->tb_invoicenumber_theinvoice->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_invoicenumber_theinvoice->Name = L"tb_invoicenumber_theinvoice";
			this->tb_invoicenumber_theinvoice->Size = System::Drawing::Size(611, 30);
			this->tb_invoicenumber_theinvoice->TabIndex = 2;
			this->tb_invoicenumber_theinvoice->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->tb_invoicenumber_theinvoice->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::tb_invoicenumber_theinvoice_KeyPress);
			// 
			// lb_date_theinvice
			// 
			this->lb_date_theinvice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_date_theinvice->Location = System::Drawing::Point(3, 50);
			this->lb_date_theinvice->Name = L"lb_date_theinvice";
			this->lb_date_theinvice->Size = System::Drawing::Size(236, 42);
			this->lb_date_theinvice->TabIndex = 1;
			this->lb_date_theinvice->Text = L"The date:";
			// 
			// lb_invoicenumber_theinvoice
			// 
			this->lb_invoicenumber_theinvoice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 13.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_invoicenumber_theinvoice->Location = System::Drawing::Point(3, 2);
			this->lb_invoicenumber_theinvoice->Name = L"lb_invoicenumber_theinvoice";
			this->lb_invoicenumber_theinvoice->Size = System::Drawing::Size(236, 42);
			this->lb_invoicenumber_theinvoice->TabIndex = 0;
			this->lb_invoicenumber_theinvoice->Text = L"Invoice number:";
			// 
			// lb_theinvoice
			// 
			this->lb_theinvoice->Dock = System::Windows::Forms::DockStyle::Top;
			this->lb_theinvoice->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_theinvoice->Location = System::Drawing::Point(0, 0);
			this->lb_theinvoice->Name = L"lb_theinvoice";
			this->lb_theinvoice->Size = System::Drawing::Size(1189, 127);
			this->lb_theinvoice->TabIndex = 1;
			this->lb_theinvoice->Text = L"Total Bill";
			this->lb_theinvoice->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pn_left_bar
			// 
			this->pn_left_bar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_left_bar->Controls->Add(this->flowLayoutPanel1);
			this->pn_left_bar->Controls->Add(this->pn_picture);
			this->pn_left_bar->Dock = System::Windows::Forms::DockStyle::Left;
			this->pn_left_bar->Location = System::Drawing::Point(0, 0);
			this->pn_left_bar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_left_bar->Name = L"pn_left_bar";
			this->pn_left_bar->Size = System::Drawing::Size(296, 745);
			this->pn_left_bar->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->btn_edit_information);
			this->flowLayoutPanel1->Controls->Add(this->btn_products);
			this->flowLayoutPanel1->Controls->Add(this->btn_orders);
			this->flowLayoutPanel1->Controls->Add(this->btn_TotalBill);
			this->flowLayoutPanel1->Controls->Add(this->btn_login);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 201);
			this->flowLayoutPanel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(296, 544);
			this->flowLayoutPanel1->TabIndex = 1;
			// 
			// btn_edit_information
			// 
			this->btn_edit_information->BackColor = System::Drawing::Color::DimGray;
			this->btn_edit_information->FlatAppearance->BorderSize = 0;
			this->btn_edit_information->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_edit_information->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_edit_information->ForeColor = System::Drawing::Color::White;
			this->btn_edit_information->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_edit_information.Image")));
			this->btn_edit_information->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_edit_information->Location = System::Drawing::Point(3, 2);
			this->btn_edit_information->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_edit_information->Name = L"btn_edit_information";
			this->btn_edit_information->Size = System::Drawing::Size(293, 74);
			this->btn_edit_information->TabIndex = 0;
			this->btn_edit_information->Text = L"Edit Information";
			this->btn_edit_information->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_edit_information->UseVisualStyleBackColor = false;
			this->btn_edit_information->Click += gcnew System::EventHandler(this, &MyForm::btn_edit_information_Click);
			this->btn_edit_information->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_edit_information_MouseEnter);
			this->btn_edit_information->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_edit_information_MouseLeave);
			// 
			// btn_products
			// 
			this->btn_products->FlatAppearance->BorderSize = 0;
			this->btn_products->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_products->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_products->ForeColor = System::Drawing::Color::White;
			this->btn_products->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_products.Image")));
			this->btn_products->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_products->Location = System::Drawing::Point(3, 80);
			this->btn_products->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_products->Name = L"btn_products";
			this->btn_products->Size = System::Drawing::Size(293, 74);
			this->btn_products->TabIndex = 1;
			this->btn_products->Text = L"Products";
			this->btn_products->UseVisualStyleBackColor = true;
			this->btn_products->Click += gcnew System::EventHandler(this, &MyForm::btn_products_Click);
			this->btn_products->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_products_MouseEnter);
			this->btn_products->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_products_MouseLeave);
			// 
			// btn_orders
			// 
			this->btn_orders->FlatAppearance->BorderSize = 0;
			this->btn_orders->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_orders->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_orders->ForeColor = System::Drawing::Color::White;
			this->btn_orders->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_orders.Image")));
			this->btn_orders->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_orders->Location = System::Drawing::Point(3, 158);
			this->btn_orders->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_orders->Name = L"btn_orders";
			this->btn_orders->Size = System::Drawing::Size(293, 74);
			this->btn_orders->TabIndex = 2;
			this->btn_orders->Text = L"Orders";
			this->btn_orders->UseVisualStyleBackColor = true;
			this->btn_orders->Click += gcnew System::EventHandler(this, &MyForm::btn_orders_Click);
			this->btn_orders->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_orders_MouseEnter);
			this->btn_orders->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_orders_MouseLeave);
			// 
			// btn_TotalBill
			// 
			this->btn_TotalBill->FlatAppearance->BorderSize = 0;
			this->btn_TotalBill->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_TotalBill->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_TotalBill->ForeColor = System::Drawing::Color::White;
			this->btn_TotalBill->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_TotalBill.Image")));
			this->btn_TotalBill->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_TotalBill->Location = System::Drawing::Point(3, 236);
			this->btn_TotalBill->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_TotalBill->Name = L"btn_TotalBill";
			this->btn_TotalBill->Size = System::Drawing::Size(293, 74);
			this->btn_TotalBill->TabIndex = 4;
			this->btn_TotalBill->Text = L"Total Bill";
			this->btn_TotalBill->UseVisualStyleBackColor = true;
			this->btn_TotalBill->Click += gcnew System::EventHandler(this, &MyForm::btn_TotalBill_Click);
			this->btn_TotalBill->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_TotalBill_MouseEnter);
			this->btn_TotalBill->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_TotalBill_MouseLeave);
			// 
			// btn_login
			// 
			this->btn_login->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->btn_login->FlatAppearance->BorderSize = 0;
			this->btn_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_login->ForeColor = System::Drawing::Color::White;
			this->btn_login->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_login.Image")));
			this->btn_login->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_login->Location = System::Drawing::Point(3, 397);
			this->btn_login->Margin = System::Windows::Forms::Padding(3, 85, 3, 2);
			this->btn_login->Name = L"btn_login";
			this->btn_login->Size = System::Drawing::Size(293, 98);
			this->btn_login->TabIndex = 3;
			this->btn_login->Text = L"Log out";
			this->btn_login->UseVisualStyleBackColor = true;
			this->btn_login->Click += gcnew System::EventHandler(this, &MyForm::btn_logout_Click);
			// 
			// pn_picture
			// 
			this->pn_picture->Controls->Add(this->lb_profile);
			this->pn_picture->Controls->Add(this->pb_profile);
			this->pn_picture->Dock = System::Windows::Forms::DockStyle::Top;
			this->pn_picture->Location = System::Drawing::Point(0, 0);
			this->pn_picture->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_picture->Name = L"pn_picture";
			this->pn_picture->Size = System::Drawing::Size(296, 201);
			this->pn_picture->TabIndex = 0;
			// 
			// lb_profile
			// 
			this->lb_profile->BackColor = System::Drawing::Color::Transparent;
			this->lb_profile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_profile->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->lb_profile->Location = System::Drawing::Point(52, 169);
			this->lb_profile->Name = L"lb_profile";
			this->lb_profile->Size = System::Drawing::Size(197, 23);
			this->lb_profile->TabIndex = 1;
			this->lb_profile->Text = L"USERNAME";
			this->lb_profile->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pb_profile
			// 
			this->pb_profile->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_profile.BackgroundImage")));
			this->pb_profile->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pb_profile->Location = System::Drawing::Point(45, 5);
			this->pb_profile->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pb_profile->Name = L"pb_profile";
			this->pb_profile->Size = System::Drawing::Size(204, 161);
			this->pb_profile->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pb_profile->TabIndex = 0;
			this->pb_profile->TabStop = false;
			// 
			// pn_start
			// 
			this->pn_start->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_start->Controls->Add(this->label25);
			this->pn_start->Controls->Add(this->label24);
			this->pn_start->Controls->Add(this->pictureBox5);
			this->pn_start->Controls->Add(this->pictureBox4);
			this->pn_start->Controls->Add(this->label23);
			this->pn_start->Controls->Add(this->pictureBox3);
			this->pn_start->Controls->Add(this->label21);
			this->pn_start->Controls->Add(this->label18);
			this->pn_start->Controls->Add(this->label20);
			this->pn_start->Controls->Add(this->btn_start);
			this->pn_start->Controls->Add(this->btn_exit);
			this->pn_start->Controls->Add(this->welcomeScreen);
			this->pn_start->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_start->Location = System::Drawing::Point(0, 0);
			this->pn_start->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_start->Name = L"pn_start";
			this->pn_start->Size = System::Drawing::Size(1485, 745);
			this->pn_start->TabIndex = 3;
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->BackColor = System::Drawing::Color::White;
			this->label25->Font = (gcnew System::Drawing::Font(L"Britannic Bold", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->Location = System::Drawing::Point(1048, 79);
			this->label25->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(178, 30);
			this->label25->TabIndex = 11;
			this->label25->Text = L"SUPERMARKO";
			this->label25->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label24
			// 
			this->label24->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->label24->Location = System::Drawing::Point(56, 363);
			this->label24->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(13, 150);
			this->label24->TabIndex = 10;
			// 
			// pictureBox5
			// 
			this->pictureBox5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox5.Image")));
			this->pictureBox5->Location = System::Drawing::Point(153, 203);
			this->pictureBox5->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox5->Name = L"pictureBox5";
			this->pictureBox5->Size = System::Drawing::Size(103, 25);
			this->pictureBox5->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox5->TabIndex = 9;
			this->pictureBox5->TabStop = false;
			// 
			// pictureBox4
			// 
			this->pictureBox4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox4.Image")));
			this->pictureBox4->Location = System::Drawing::Point(413, 202);
			this->pictureBox4->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox4->Name = L"pictureBox4";
			this->pictureBox4->Size = System::Drawing::Size(103, 25);
			this->pictureBox4->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox4->TabIndex = 8;
			this->pictureBox4->TabStop = false;
			// 
			// label23
			// 
			this->label23->BackColor = System::Drawing::Color::Transparent;
			this->label23->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->ForeColor = System::Drawing::Color::White;
			this->label23->Location = System::Drawing::Point(80, 358);
			this->label23->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(737, 176);
			this->label23->TabIndex = 7;
			this->label23->Text = resources->GetString(L"label23.Text");
			// 
			// pictureBox3
			// 
			this->pictureBox3->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(45, 250);
			this->pictureBox3->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(112, 106);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 6;
			this->pictureBox3->TabStop = false;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->BackColor = System::Drawing::Color::Transparent;
			this->label21->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 48, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(134)),
				static_cast<System::Int32>(static_cast<System::Byte>(6)));
			this->label21->Location = System::Drawing::Point(139, 240);
			this->label21->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(508, 111);
			this->label21->TabIndex = 5;
			this->label21->Text = L"SuperMarko";
			this->label21->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label18
			// 
			this->label18->BackColor = System::Drawing::Color::Transparent;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe Script", 48, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label18->ForeColor = System::Drawing::Color::White;
			this->label18->Location = System::Drawing::Point(83, 66);
			this->label18->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(513, 116);
			this->label18->TabIndex = 3;
			this->label18->Text = L"Welcome";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label20
			// 
			this->label20->BackColor = System::Drawing::Color::Transparent;
			this->label20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 20.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::Color::White;
			this->label20->Location = System::Drawing::Point(52, 155);
			this->label20->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(568, 132);
			this->label20->TabIndex = 4;
			this->label20->Text = L"━━━━━  TO THE  ━━━━━";
			this->label20->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btn_start
			// 
			this->btn_start->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->btn_start->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->btn_start->FlatAppearance->BorderSize = 2;
			this->btn_start->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_start->Location = System::Drawing::Point(53, 544);
			this->btn_start->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_start->Name = L"btn_start";
			this->btn_start->Size = System::Drawing::Size(225, 52);
			this->btn_start->TabIndex = 1;
			this->btn_start->Text = L"Start";
			this->btn_start->UseVisualStyleBackColor = false;
			this->btn_start->Click += gcnew System::EventHandler(this, &MyForm::btn_start_Click);
			this->btn_start->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_start_MouseEnter);
			this->btn_start->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_start_MouseLeave);
			// 
			// btn_exit
			// 
			this->btn_exit->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(218)), static_cast<System::Int32>(static_cast<System::Byte>(245)),
				static_cast<System::Int32>(static_cast<System::Byte>(242)));
			this->btn_exit->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->btn_exit->FlatAppearance->BorderSize = 2;
			this->btn_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_exit->Location = System::Drawing::Point(300, 544);
			this->btn_exit->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_exit->Name = L"btn_exit";
			this->btn_exit->Size = System::Drawing::Size(225, 52);
			this->btn_exit->TabIndex = 0;
			this->btn_exit->Text = L"Exit";
			this->btn_exit->UseVisualStyleBackColor = false;
			this->btn_exit->Click += gcnew System::EventHandler(this, &MyForm::btn_exit_Click);
			this->btn_exit->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_exit_MouseEnter);
			this->btn_exit->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_exit_MouseLeave);
			// 
			// welcomeScreen
			// 
			this->welcomeScreen->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)));
			this->welcomeScreen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"welcomeScreen.BackgroundImage")));
			this->welcomeScreen->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->welcomeScreen->Location = System::Drawing::Point(0, 0);
			this->welcomeScreen->Margin = System::Windows::Forms::Padding(4);
			this->welcomeScreen->Name = L"welcomeScreen";
			this->welcomeScreen->Size = System::Drawing::Size(1485, 745);
			this->welcomeScreen->TabIndex = 2;
			this->welcomeScreen->TabStop = false;
			// 
			// pn_register
			// 
			this->pn_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_register->Controls->Add(this->pictureBox9);
			this->pn_register->Controls->Add(this->pictureBox10);
			this->pn_register->Controls->Add(this->link_login);
			this->pn_register->Controls->Add(this->pictureBox1);
			this->pn_register->Controls->Add(this->label4);
			this->pn_register->Controls->Add(this->btn_refresh_location_register);
			this->pn_register->Controls->Add(this->btn_refresh_phonenumber_register);
			this->pn_register->Controls->Add(this->btn_refresh_password_register);
			this->pn_register->Controls->Add(this->btn_refresh_username_register);
			this->pn_register->Controls->Add(this->btn_seepassword);
			this->pn_register->Controls->Add(this->lb_location_message);
			this->pn_register->Controls->Add(this->lb_phonenumber_message);
			this->pn_register->Controls->Add(this->lb_password_message);
			this->pn_register->Controls->Add(this->lb_username_message);
			this->pn_register->Controls->Add(this->btn_register_registerpanel);
			this->pn_register->Controls->Add(this->tb_location_register);
			this->pn_register->Controls->Add(this->tb_phonenumber_register);
			this->pn_register->Controls->Add(this->tb_password_register);
			this->pn_register->Controls->Add(this->tb_username_register);
			this->pn_register->Controls->Add(this->lb_password_register);
			this->pn_register->Controls->Add(this->lb_phonenumber_register);
			this->pn_register->Controls->Add(this->lb_location);
			this->pn_register->Controls->Add(this->lb_username_register);
			this->pn_register->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_register->Location = System::Drawing::Point(0, 0);
			this->pn_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_register->Name = L"pn_register";
			this->pn_register->Size = System::Drawing::Size(1485, 745);
			this->pn_register->TabIndex = 1;
			// 
			// pictureBox9
			// 
			this->pictureBox9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox9.Image")));
			this->pictureBox9->Location = System::Drawing::Point(-39, 507);
			this->pictureBox9->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox9->Name = L"pictureBox9";
			this->pictureBox9->Size = System::Drawing::Size(432, 343);
			this->pictureBox9->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox9->TabIndex = 27;
			this->pictureBox9->TabStop = false;
			// 
			// pictureBox10
			// 
			this->pictureBox10->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox10.Image")));
			this->pictureBox10->Location = System::Drawing::Point(1093, 507);
			this->pictureBox10->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox10->Name = L"pictureBox10";
			this->pictureBox10->Size = System::Drawing::Size(432, 343);
			this->pictureBox10->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox10->TabIndex = 26;
			this->pictureBox10->TabStop = false;
			// 
			// link_login
			// 
			this->link_login->BackColor = System::Drawing::Color::DarkGray;
			this->link_login->FlatAppearance->BorderSize = 0;
			this->link_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->link_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_login->ForeColor = System::Drawing::Color::White;
			this->link_login->Location = System::Drawing::Point(664, 604);
			this->link_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->link_login->Name = L"link_login";
			this->link_login->Size = System::Drawing::Size(153, 55);
			this->link_login->TabIndex = 22;
			this->link_login->Text = L"Login";
			this->link_login->UseVisualStyleBackColor = false;
			this->link_login->Click += gcnew System::EventHandler(this, &MyForm::link_login_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(588, 54);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(87, 62);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 21;
			this->pictureBox1->TabStop = false;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 27.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(684, 48);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(233, 68);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Register";
			// 
			// btn_refresh_location_register
			// 
			this->btn_refresh_location_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_location_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_location_register.BackgroundImage")));
			this->btn_refresh_location_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_location_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_location_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_location_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_location_register->Location = System::Drawing::Point(1305, 327);
			this->btn_refresh_location_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_location_register->Name = L"btn_refresh_location_register";
			this->btn_refresh_location_register->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_location_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_location_register->TabIndex = 18;
			this->btn_refresh_location_register->UseVisualStyleBackColor = false;
			this->btn_refresh_location_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_location_register_Click);
			// 
			// btn_refresh_phonenumber_register
			// 
			this->btn_refresh_phonenumber_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_phonenumber_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_phonenumber_register.BackgroundImage")));
			this->btn_refresh_phonenumber_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_phonenumber_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_phonenumber_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_phonenumber_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_phonenumber_register->Location = System::Drawing::Point(681, 325);
			this->btn_refresh_phonenumber_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_phonenumber_register->Name = L"btn_refresh_phonenumber_register";
			this->btn_refresh_phonenumber_register->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_phonenumber_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_phonenumber_register->TabIndex = 17;
			this->btn_refresh_phonenumber_register->UseVisualStyleBackColor = false;
			this->btn_refresh_phonenumber_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_phonenumber_register_Click);
			// 
			// btn_refresh_password_register
			// 
			this->btn_refresh_password_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_password_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_password_register.BackgroundImage")));
			this->btn_refresh_password_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_password_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_password_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_password_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_password_register->Location = System::Drawing::Point(1312, 210);
			this->btn_refresh_password_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_password_register->Name = L"btn_refresh_password_register";
			this->btn_refresh_password_register->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_password_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_password_register->TabIndex = 16;
			this->btn_refresh_password_register->UseVisualStyleBackColor = false;
			this->btn_refresh_password_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_password_register_Click);
			// 
			// btn_refresh_username_register
			// 
			this->btn_refresh_username_register->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_refresh_username_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_username_register.BackgroundImage")));
			this->btn_refresh_username_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_username_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_username_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_username_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_username_register->Location = System::Drawing::Point(680, 212);
			this->btn_refresh_username_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_username_register->Name = L"btn_refresh_username_register";
			this->btn_refresh_username_register->Padding = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_username_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_username_register->TabIndex = 15;
			this->btn_refresh_username_register->UseVisualStyleBackColor = false;
			this->btn_refresh_username_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_username_register_Click);
			// 
			// btn_seepassword
			// 
			this->btn_seepassword->BackColor = System::Drawing::Color::White;
			this->btn_seepassword->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepassword.BackgroundImage")));
			this->btn_seepassword->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepassword->FlatAppearance->BorderSize = 0;
			this->btn_seepassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepassword->Location = System::Drawing::Point(1272, 209);
			this->btn_seepassword->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_seepassword->Name = L"btn_seepassword";
			this->btn_seepassword->Size = System::Drawing::Size(33, 30);
			this->btn_seepassword->TabIndex = 14;
			this->btn_seepassword->UseVisualStyleBackColor = false;
			this->btn_seepassword->Click += gcnew System::EventHandler(this, &MyForm::btn_seepassword_Click);
			// 
			// lb_location_message
			// 
			this->lb_location_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_location_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_location_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_location_message->Location = System::Drawing::Point(979, 366);
			this->lb_location_message->Name = L"lb_location_message";
			this->lb_location_message->Size = System::Drawing::Size(325, 66);
			this->lb_location_message->TabIndex = 12;
			this->lb_location_message->Text = L"Enter the location";
			// 
			// lb_phonenumber_message
			// 
			this->lb_phonenumber_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_phonenumber_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_phonenumber_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_phonenumber_message->Location = System::Drawing::Point(351, 362);
			this->lb_phonenumber_message->Name = L"lb_phonenumber_message";
			this->lb_phonenumber_message->Size = System::Drawing::Size(325, 73);
			this->lb_phonenumber_message->TabIndex = 11;
			this->lb_phonenumber_message->Text = L"Enter the phone number";
			// 
			// lb_password_message
			// 
			this->lb_password_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_password_message->Location = System::Drawing::Point(981, 250);
			this->lb_password_message->Name = L"lb_password_message";
			this->lb_password_message->Size = System::Drawing::Size(325, 49);
			this->lb_password_message->TabIndex = 10;
			this->lb_password_message->Text = L"Enter the password";
			// 
			// lb_username_message
			// 
			this->lb_username_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_username_message->Location = System::Drawing::Point(348, 250);
			this->lb_username_message->Name = L"lb_username_message";
			this->lb_username_message->Size = System::Drawing::Size(325, 62);
			this->lb_username_message->TabIndex = 9;
			this->lb_username_message->Text = L"Enter the username";
			// 
			// btn_register_registerpanel
			// 
			this->btn_register_registerpanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_register_registerpanel->FlatAppearance->BorderSize = 0;
			this->btn_register_registerpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_register_registerpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_register_registerpanel->ForeColor = System::Drawing::Color::White;
			this->btn_register_registerpanel->Location = System::Drawing::Point(628, 519);
			this->btn_register_registerpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_register_registerpanel->Name = L"btn_register_registerpanel";
			this->btn_register_registerpanel->Size = System::Drawing::Size(227, 58);
			this->btn_register_registerpanel->TabIndex = 8;
			this->btn_register_registerpanel->Text = L"Register";
			this->btn_register_registerpanel->UseVisualStyleBackColor = false;
			this->btn_register_registerpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_register_registerpanel_Click);
			// 
			// tb_location_register
			// 
			this->tb_location_register->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_location_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_location_register->Location = System::Drawing::Point(975, 320);
			this->tb_location_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_location_register->Name = L"tb_location_register";
			this->tb_location_register->Size = System::Drawing::Size(326, 39);
			this->tb_location_register->TabIndex = 7;
			// 
			// tb_phonenumber_register
			// 
			this->tb_phonenumber_register->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_phonenumber_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_phonenumber_register->Location = System::Drawing::Point(351, 318);
			this->tb_phonenumber_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_phonenumber_register->Name = L"tb_phonenumber_register";
			this->tb_phonenumber_register->Size = System::Drawing::Size(326, 39);
			this->tb_phonenumber_register->TabIndex = 6;
			// 
			// tb_password_register
			// 
			this->tb_password_register->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_password_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_password_register->Location = System::Drawing::Point(981, 203);
			this->tb_password_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_password_register->Name = L"tb_password_register";
			this->tb_password_register->Size = System::Drawing::Size(326, 39);
			this->tb_password_register->TabIndex = 5;
			this->tb_password_register->UseSystemPasswordChar = true;
			// 
			// tb_username_register
			// 
			this->tb_username_register->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->tb_username_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_username_register->Location = System::Drawing::Point(348, 203);
			this->tb_username_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_username_register->Name = L"tb_username_register";
			this->tb_username_register->Size = System::Drawing::Size(326, 39);
			this->tb_username_register->TabIndex = 4;
			// 
			// lb_password_register
			// 
			this->lb_password_register->AutoSize = true;
			this->lb_password_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_password_register->ForeColor = System::Drawing::Color::White;
			this->lb_password_register->Location = System::Drawing::Point(779, 204);
			this->lb_password_register->Name = L"lb_password_register";
			this->lb_password_register->Size = System::Drawing::Size(166, 41);
			this->lb_password_register->TabIndex = 3;
			this->lb_password_register->Text = L"Password :";
			// 
			// lb_phonenumber_register
			// 
			this->lb_phonenumber_register->AutoSize = true;
			this->lb_phonenumber_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_phonenumber_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_phonenumber_register->ForeColor = System::Drawing::Color::White;
			this->lb_phonenumber_register->Location = System::Drawing::Point(83, 314);
			this->lb_phonenumber_register->Name = L"lb_phonenumber_register";
			this->lb_phonenumber_register->Size = System::Drawing::Size(240, 41);
			this->lb_phonenumber_register->TabIndex = 2;
			this->lb_phonenumber_register->Text = L"Phone number :";
			// 
			// lb_location
			// 
			this->lb_location->AutoSize = true;
			this->lb_location->BackColor = System::Drawing::Color::Transparent;
			this->lb_location->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_location->ForeColor = System::Drawing::Color::White;
			this->lb_location->Location = System::Drawing::Point(779, 319);
			this->lb_location->Name = L"lb_location";
			this->lb_location->Size = System::Drawing::Size(154, 41);
			this->lb_location->TabIndex = 1;
			this->lb_location->Text = L"Location :";
			// 
			// lb_username_register
			// 
			this->lb_username_register->AutoSize = true;
			this->lb_username_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_register->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_username_register->ForeColor = System::Drawing::Color::White;
			this->lb_username_register->Location = System::Drawing::Point(132, 198);
			this->lb_username_register->Name = L"lb_username_register";
			this->lb_username_register->Size = System::Drawing::Size(174, 41);
			this->lb_username_register->TabIndex = 0;
			this->lb_username_register->Text = L"Username :";
			// 
			// pn_thankyou
			// 
			this->pn_thankyou->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_thankyou->Controls->Add(this->axWindowsMediaPlayer1);
			this->pn_thankyou->Location = System::Drawing::Point(0, 0);
			this->pn_thankyou->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_thankyou->Name = L"pn_thankyou";
			this->pn_thankyou->Size = System::Drawing::Size(1485, 745);
			this->pn_thankyou->TabIndex = 0;
			// 
			// axWindowsMediaPlayer1
			// 
			this->axWindowsMediaPlayer1->Enabled = true;
			this->axWindowsMediaPlayer1->Location = System::Drawing::Point(2, 0);
			this->axWindowsMediaPlayer1->Margin = System::Windows::Forms::Padding(4);
			this->axWindowsMediaPlayer1->Name = L"axWindowsMediaPlayer1";
			this->axWindowsMediaPlayer1->OcxState = (cli::safe_cast<System::Windows::Forms::AxHost::State^>(resources->GetObject(L"axWindowsMediaPlayer1.OcxState")));
			this->axWindowsMediaPlayer1->Size = System::Drawing::Size(1110, 602);
			this->axWindowsMediaPlayer1->TabIndex = 12;
			this->axWindowsMediaPlayer1->PlayStateChange += gcnew AxWMPLib::_WMPOCXEvents_PlayStateChangeEventHandler(this, &MyForm::axWindowsMediaPlayer1_PlayStateChange_1);
			// 
			// timerforexit
			// 
			this->timerforexit->Interval = 3000;
			this->timerforexit->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// printPreviewDialog1
			// 
			this->printPreviewDialog1->AutoScrollMargin = System::Drawing::Size(0, 0);
			this->printPreviewDialog1->AutoScrollMinSize = System::Drawing::Size(0, 0);
			this->printPreviewDialog1->ClientSize = System::Drawing::Size(400, 300);
			this->printPreviewDialog1->Document = this->printDocument1;
			this->printPreviewDialog1->Enabled = true;
			this->printPreviewDialog1->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"printPreviewDialog1.Icon")));
			this->printPreviewDialog1->Name = L"printPreviewDialog1";
			this->printPreviewDialog1->Visible = false;
			// 
			// printDocument1
			// 
			this->printDocument1->PrintPage += gcnew System::Drawing::Printing::PrintPageEventHandler(this, &MyForm::printDocument1_PrintPage);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1485, 800);
			this->Controls->Add(this->pn_main_dashboard);
			this->Controls->Add(this->pn_upper_bar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SuperMarko";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->pn_upper_bar->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->EndInit();
			this->pn_main_dashboard->ResumeLayout(false);
			this->pn_login->ResumeLayout(false);
			this->pn_login->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->pn_defualt->ResumeLayout(false);
			this->pn_edit_information->ResumeLayout(false);
			this->pn_currentInfo->ResumeLayout(false);
			this->pn_currentInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox13))->EndInit();
			this->pn_editInfo->ResumeLayout(false);
			this->pn_editInfo->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox11))->EndInit();
			this->pn_resetPassword->ResumeLayout(false);
			this->pn_resetPassword->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox12))->EndInit();
			this->pn_blank->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->EndInit();
			this->pn_products->ResumeLayout(false);
			this->pn_main_category->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->pn_pet_supplies_category->ResumeLayout(false);
			this->pn_household_category->ResumeLayout(false);
			this->pn_snacks_category->ResumeLayout(false);
			this->pn_bakery_category->ResumeLayout(false);
			this->pn_poultry_category->ResumeLayout(false);
			this->pn_seafood_category->ResumeLayout(false);
			this->pn_butchershop_category->ResumeLayout(false);
			this->pn_dairy_category->ResumeLayout(false);
			this->pn_vegetable_category->ResumeLayout(false);
			this->pn_fruits_category->ResumeLayout(false);
			this->pn_orders->ResumeLayout(false);
			this->pn_viewBill->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_theinvoice))->EndInit();
			this->pn->ResumeLayout(false);
			this->pn->PerformLayout();
			this->flowLayoutPanel13->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			this->panel2->ResumeLayout(false);
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_picture->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->EndInit();
			this->pn_start->ResumeLayout(false);
			this->pn_start->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->EndInit();
			this->pn_register->ResumeLayout(false);
			this->pn_register->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox10))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->pn_thankyou->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->axWindowsMediaPlayer1))->EndInit();
			this->ResumeLayout(false);

		}
		//the code start here
#pragma endregion
		System::Void SuperMarkoGUI::MyForm::btn_seepassword_editinfo_Click(System::Object^ sender, System::EventArgs^ e) {
			tb_currentPassword->UseSystemPasswordChar = !tb_currentPassword->UseSystemPasswordChar;
		}

	private:
		int currentCustomerIndex;
		array<CUSTOMER^>^ customers;
		array<ORDER^>^ orders;
		array<array<PRODUCT^>^>^ products;
		array<int>^ productCounts;

		    //myform
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_start);
		
		
		pn->Visible = false;	
		Label^ lb = gcnew Label();
		lb->Text = "Please confirm your order";
		lb->Font = gcnew System::Drawing::Font("sign ui", 20, FontStyle::Bold);
		lb->ForeColor = System::Drawing::Color::DarkRed;
		lb->Location = System::Drawing::Point(300,250);
		lb->AutoSize = true;
		
		pn_viewBill->Controls->Add(lb);
		dataGridView1->ColumnHeadersDefaultCellStyle->Font = gcnew System::Drawing::Font("sign ui", 14, FontStyle::Bold);
		dataGridView1->ColumnHeadersDefaultCellStyle->ForeColor = System::Drawing::Color::DarkRed;
		dataGridView1->ColumnHeadersDefaultCellStyle->BackColor = System::Drawing::Color::LightGray;
	}
	   
		   //pn_thankyou
    private: System::Void axWindowsMediaPlayer1_PlayStateChange_1(System::Object^ sender, AxWMPLib::_WMPOCXEvents_PlayStateChangeEvent^ e) {

	if (e->newState == 3) {

		axWindowsMediaPlayer1->Visible = true;


		for each (Control ^ ctrl in pn_thankyou->Controls) {
			if (dynamic_cast<PictureBox^>(ctrl)) {
				pn_thankyou->Controls->Remove(ctrl);
				break;
			}
		}
	}

	if (e->newState == 8) {
		// Show a static image when playback ends
		String^ endImage = "images/thankyou_thumbnail.jpg";
		if (System::IO::File::Exists(endImage)) {
			// Set a static image as the background
			axWindowsMediaPlayer1->Visible = false;

			PictureBox^ endScreen = gcnew PictureBox();
			endScreen->Dock = DockStyle::Fill;
			endScreen->SizeMode = PictureBoxSizeMode::StretchImage;
			endScreen->Image = Image::FromFile(endImage);
			pn_thankyou->Controls->Add(endScreen);
			endScreen->BringToFront();
		}
	}
}
		  
		   //pn_upper_bar
	private: System::Void btn_close_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: System::Void button1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->ForeColor = Color::FromArgb(0xE6, 0x34, 0x62);
	}
	
		   //pn_login
	private: System::Void btn_login_loginpanel_Click(System::Object^ sender, System::EventArgs^ e) {
	// Clear previous error messages
	lb_username_message_login->Visible = false;
	lb_password_message_login->Visible = false;

	// Check if username or password text boxes are empty
	bool hasError = false;

	// Check if the username is empty
	if (String::IsNullOrEmpty(tb_username_login->Text->Trim())) {
		lb_username_message_login->Visible = true;
		lb_username_message_login->Text = "Please enter the username.";
		hasError = true;
	}

	// Check if the password is empty
	if (String::IsNullOrEmpty(tb_password_login->Text->Trim())) {
		lb_password_message_login->Visible = true;
		lb_password_message_login->Text = "Please enter the password.";
		hasError = true;
	}

	// If there are errors, focus on the first empty field and return
	if (hasError) {
		if (String::IsNullOrEmpty(tb_username_login->Text->Trim())) {
			tb_username_login->Focus();
		}
		else {
			tb_password_login->Focus();
		}
		return;
	}

	// Open the file to check for user credentials
	StreamReader^ sr = nullptr;
	try {
		sr = gcnew StreamReader("customers.txt");
		String^ line = "";
		int index = 0;
		bool userFound = false;
		bool passwordCorrect = false;

		while ((line = sr->ReadLine()) != nullptr) {
			array<String^>^ parts = line->Split(',');
			if (parts->Length < 5) continue;

			String^ fileID = parts[0]->Trim();
			String^ fileUser = parts[1]->Trim();
			String^ filePhone = parts[2]->Trim();
			String^ fileLocation = parts[3]->Trim();
			String^ filePass = parts[4]->Trim();

			// Check if the username exists
			if (tb_username_login->Text->Trim() == fileUser) {
				userFound = true;

				// If username exists, check if the password matches
				if (tb_password_login->Text->Trim() == filePass) {
					passwordCorrect = true;

					// Create a new customer object and set the current customer
					CUSTOMER^ c = gcnew CUSTOMER();
					c->ID = Convert::ToInt32(fileID);
					c->Name = fileUser;
					c->Password = filePass;
					c->PhoneNumber = filePhone;
					c->Location = fileLocation;
					customers[index] = c;

					currentCustomerIndex = index;
					lb_profile->Text = fileUser->ToUpper();
					tb_customername_theincoive->Text = fileUser->ToUpper();

					// Show the main panel and reset the login fields
					showPanel(pn_defualt);
					showPanel(pn_blank);
					tb_username_login->Text = "";
					tb_password_login->Text = "";
					sr->Close();
					return;
				}
				else {
					// If password does not match, break the loop
					break;
				}
			}
			index++;
		}
		sr->Close();

		// Handle cases based on the results
		if (userFound && !passwordCorrect) {
			lb_password_message_login->Visible = true;
			lb_password_message_login->Text = "Password is incorrect.";
			tb_password_login->Focus();
		}
		else if (!userFound) {
			MessageBox::Show("There is no such a user.", "Login Failed", MessageBoxButtons::OK, MessageBoxIcon::Error);
			tb_username_login->Focus();
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("An error occurred while reading the user data: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}
	finally {
		if (sr != nullptr) {
			sr->Close();
		}
	}
}
	private: System::Void btn_back_loginpanal_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_start);
	}
	private: System::Void btn_register_loginpanel_Click(System::Object^ sender, System::EventArgs^ e) {
		lb_password_message_login->Text = ("Enter the password");
		lb_username_message_login->Text = ("Enter the username");
		tb_username_login->Text = "";
		tb_password_login->Text = "";

		showPanel(pn_register);
	}
	private: System::Void btn_refresh_username_login_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_username_login->Text = "";
	}
	private: System::Void btn_refresh_password_login_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_password_login->Text = "";
	}
	private: System::Void btn_seepasword_login_Click(System::Object^ sender, System::EventArgs^ e) {
		if (tb_password_login->UseSystemPasswordChar == false)
		{
			tb_password_login->UseSystemPasswordChar = true;
		}
		else
		{
			tb_password_login->UseSystemPasswordChar = false;
		}
	}
	
		 //pn_register
	private: System::Void btn_register_registerpanel_Click(System::Object^ sender, System::EventArgs^ e) {
		bool hasError = false;

		// Extract input values
		String^ username = tb_username_register->Text->Trim();
		String^ password = tb_password_register->Text->Trim();
		String^ phone = tb_phonenumber_register->Text->Trim();
		String^ location = tb_location_register->Text->Trim();

		// === Password Validation ===
		if (!validatePassword(password, lb_password_message)) {
			tb_password_register->Focus();
			tb_password_register->SelectAll();
			return; // Stop registration if validation fails
		}
		else {
			lb_password_message->Text = "";
		}

		// === Phone Number Validation ===
		if (!validatePhoneNumber(phone, lb_phonenumber_message)) {
			tb_phonenumber_register->Focus();
			tb_phonenumber_register->SelectAll();
			hasError = true;
		}
		else {
			lb_phonenumber_message->Text = "";
		}

		// === Username Validation ===
		bool usernameExists = false;
		if (File::Exists("customers.txt")) {
			for each (String ^ line in File::ReadAllLines("customers.txt")) {
				array<String^>^ parts = line->Split(',');
				if (parts->Length >= 2 && parts[1]->Trim() == username) {
					usernameExists = true;
					break;
				}
			}
		}

		if (!validateUsername(username, lb_username_message)) {
			tb_username_register->Focus();
			tb_username_register->SelectAll();
			hasError = true;
		}
		else if (usernameExists) {
			lb_username_message->Text = "Username already exists.";
			hasError = true;
		}
		else {
			lb_username_message->Text = "";
		}

		// === Location Validation ===
		if (!validateLocation(location, lb_location_message)) {
			tb_location_register->Focus();
			tb_location_register->SelectAll();
			hasError = true;
		}
		else {
			lb_location_message->Text = "";
		}

		// === Stop if any validation failed ===
		if (hasError) return;

		// === Generate Customer ID ===
		int newCustomerID = 1; // Default ID
		if (File::Exists("customers.txt")) {
			array<String^>^ allCustomers = File::ReadAllLines("customers.txt");
			newCustomerID = allCustomers->Length + 1;
		}

		// === Save to Struct ===
		CUSTOMER^ newCustomer = gcnew CUSTOMER();
		newCustomer->ID = newCustomerID;
		newCustomer->Name = username;
		newCustomer->PhoneNumber = phone;
		newCustomer->Location = location;
		newCustomer->Password = password;

		if (newCustomerID <= numOfCustomers) {
			customers[newCustomerID - 1] = newCustomer;
		}

		// === Save to File ===	
		try {
			StreamWriter^ sw = gcnew StreamWriter("customers.txt", true);
			String^ line = newCustomerID.ToString() + "," + username + "," + phone + "," + location + "," + password;
			sw->WriteLine(line);
			sw->Close();

			MessageBox::Show("Registration successful!");

			// Bring login panel to front
			showPanel(pn_login);

			// Clear all TextBoxes inside pn_register
			for each (Control ^ c in pn_register->Controls) {
				if (TextBox^ tb = dynamic_cast<TextBox^>(c)) {
					tb->Clear();
				}
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error: " + ex->Message);
		}
	}
	private: System::Void btn_refresh_username_register_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_username_register->Text = "";
	}
	private: System::Void btn_refresh_password_register_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_password_register->Text = "";
	}
	private: System::Void btn_refresh_phonenumber_register_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_phonenumber_register->Text = "";
	}
	private: System::Void btn_refresh_location_register_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_location_register->Text = "";
	}
	private: System::Void linklogin_LinkClicked(System::Object^ sender, System::Windows::Forms::LinkLabelLinkClickedEventArgs^ e) {
		tb_location_register->Text = "";
		tb_password_register->Text = "";
		tb_phonenumber_register->Text = "";
		tb_username_register->Text = "";
		lb_location_message->Text = ("Enter the location");
		lb_phonenumber_message->Text = ("Enter the phone number");
		lb_password_message->Text = ("Enter the password");
		lb_username_message->Text = ("Enter the username");

		showPanel(pn_login);
	}
	private: System::Void btn_seepassword_Click(System::Object^ sender, System::EventArgs^ e) {
		if (tb_password_register->UseSystemPasswordChar == false)
		{
			tb_password_register->UseSystemPasswordChar = true;
		}
		else
		{
			tb_password_register->UseSystemPasswordChar = false;
		}
	}
	private: System::Void link_login_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_username_login->Text = "";
		tb_password_login->Text = "";
		lb_username_message_login->Text = ("Enter the username");
		lb_password_message_login->Text = ("Enter the password");
		showPanel(pn_login);
	}
	   
		   //pn_start
    private: System::Void btn_exit_Click(System::Object^ sender, System::EventArgs^ e) {
	// In the btn_exit_Click method, after setting up the media player:
	axWindowsMediaPlayer1->uiMode = "none";
	axWindowsMediaPlayer1->URL = "images/Thank you.mp4";
	axWindowsMediaPlayer1->settings->mute = true;
	axWindowsMediaPlayer1->settings->autoStart = true;
	axWindowsMediaPlayer1->settings->enableErrorDialogs = false;
	axWindowsMediaPlayer1->settings->setMode("loop", false);
	axWindowsMediaPlayer1->Ctlcontrols->play();
	axWindowsMediaPlayer1->Visible = false; 
	showPanel(pn_thankyou);
	// Add this to display an image when video ends



	// Set the timer to exit after 15 seconds

	timerforexit->Interval = 20000; // 15 seconds
 	timerforexit->Start();
    }
	private: System::Void btn_exit_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->BackColor = Color::FromArgb(230, 52, 98);
		btn_exit->ForeColor = Color::White;
	}
	private: System::Void btn_exit_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->BackColor = Color::FromArgb(218, 245, 242);
    	btn_exit->ForeColor = Color::Black;
	}
	private: System::Void btn_start_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_start->BackColor = Color::FromArgb(123, 255, 149);
		btn_start->ForeColor = Color::White;
	}
	private: System::Void btn_start_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btn_start->BackColor = Color::FromArgb(218, 245, 242);
		btn_start->ForeColor = Color::Black;
	}
	private: System::Void btn_start_MouseHover(System::Object^ sender, System::EventArgs^ e) {
		btn_start->ForeColor = Color::Wheat;
	}
	private: System::Void btn_start_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_login);
	}
    private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	timerforexit->Stop();  // Stop the timer
	Application::Exit();   // Now exit nicely
    }
	private: System::Void timer1_Tick_1(System::Object^ sender, System::EventArgs^ e) {
			 this->Close();
    }
     
		   //----------------------------------------pn_default--------------------------------------------------

		   //Edit Information
    private: System::Void btn_edit_information_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
			   if (btn_edit_information != selectedButton) {
				   btn_edit_information->BackColor = Color::DimGray;
			   }
		   }
	private: System::Void btn_edit_information_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (btn_edit_information != selectedButton) {
			btn_edit_information->BackColor = Color::Transparent;
		}
	}
	private: System::Void btn_edit_information_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedButton = btn_edit_information;
		showPanel(pn_edit_information);
		showCategoryPanel(pn_currentInfo);
		populateCurrentUserInfo(sender, e);
		MenuBGColor(btn_edit_information);
	}
	private: System::Void btn_saveEdit_Click(System::Object^ sender, System::EventArgs^ e) {
		try {
			// Extract input values
			String^ newName = tb_edit_username->Text->Trim();
			String^ newPhone = tb_edit_phonenumber->Text->Trim();
			String^ newLocation = tb_edit_location->Text->Trim();
			String^ newPassword = tb_currentPassword->Text->Trim(); // optional to validate

			bool hasError = false;
			String^ currentID = customers[currentCustomerIndex]->ID.ToString();

			// === Phone Validation ===
			if (!validatePhoneNumber(newPhone,lb_errorPhone)) {
				lb_errorPhone->Visible = true;
				tb_edit_phonenumber->Focus();
				tb_edit_phonenumber->SelectAll();
				hasError = true;
			}
			else {
				lb_errorPhone->Visible = false;
			}

			// === Name Validation ===
			if (!validateUsername(newName, lb_errorUsername)) {
				lb_errorUsername->Visible = true;
				tb_edit_username->Focus();
				tb_edit_username->SelectAll();
				hasError = true;
			}
			else {
				lb_errorUsername->Visible = false;
			}

			if (true){
				// Check if name already exists (excluding current user)
				array<String^>^ lines = File::ReadAllLines("customers.txt");
				for each (String ^ line in lines) {
					array<String^>^ parts = line->Split(',');
					if (parts->Length < 5) continue;

					if (parts[1]->Trim()->ToLower() == newName->ToLower() && parts[0]->Trim() != currentID) {
						lb_errorUsername->Visible = true;
						lb_errorUsername->Text = "This name is already taken by another user.";
						tb_edit_username->Focus();
						tb_edit_username->SelectAll();
						hasError = true;
						break;
					}
				}
			}
			else {

				lb_errorUsername->Visible = false;
			}

			// === Location Validation ===
			if (!validateLocation(newLocation, lb_errorLocation)) {
				lb_errorLocation->Visible = true;
				tb_edit_location->Focus();
				tb_edit_location->SelectAll();
				hasError = true;
			}
			else {
				lb_errorLocation->Visible = false;
			}

			if (hasError) return;

			// === Update Customer in File ===
			array<String^>^ linesToUpdate = File::ReadAllLines("customers.txt");

			for (int i = 0; i < linesToUpdate->Length; i++) {
				array<String^>^ parts = linesToUpdate[i]->Split(',');
				if (parts->Length < 5) continue;

				if (parts[0]->Trim() == currentID) {
					String^ updatedLine = currentID + "," +
						newName + "," +
						newPhone + "," +
						newLocation + "," +
						newPassword;

					linesToUpdate[i] = updatedLine;
					break;
				}
			}

			File::WriteAllLines("customers.txt", linesToUpdate);
			MessageBox::Show("Customer info updated successfully!");
			tb_currentUsername->Text = newName;
			tb_currentPhoneNumber->Text = newPhone;
			tb_currentLocation->Text = newLocation;
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error while saving: " + ex->Message);
		}

		showCategoryPanel(pn_currentInfo);
	}
	private: System::Void btn_cancelEdit_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_currentInfo->BringToFront();
	}
	private: System::Void btn_reset_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_resetPassword->BringToFront();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		tb_newPassword->Text = "";
		tb_confirmPassword->Text = "";
		pn_currentInfo->BringToFront();
	}
	
		   //Reset Password
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		//save new password
		String^ newPassword = tb_newPassword->Text->Trim();
		String^ confirmPassword = tb_confirmPassword->Text->Trim();


		if (!validatePassword(newPassword,lb_newpassword)) {
			lb_newpassword->Visible = true;
			tb_newPassword->Focus();
			tb_newPassword->SelectAll();
			return;
		}
		else {
			lb_newpassword->Visible = false;
		}
		if (newPassword != confirmPassword) {
			lb_newpassword->Text = "Passwords do not match";
			lb_newpassword->Visible = true;
			tb_confirmPassword->Focus();
			tb_confirmPassword->SelectAll();
			return;
		}
		else {
			lb_newpassword->Visible = false;
		}
		//update password in the file
		array<String^>^ lines = File::ReadAllLines("customers.txt");
		for (int i = 0; i < lines->Length; i++) {
			array<String^>^ parts = lines[i]->Split(',');
			if (parts->Length < 5) continue;
			if (parts[0]->Trim() == customers[currentCustomerIndex]->ID.ToString()) {
				parts[4] = newPassword;
				lines[i] = String::Join(",", parts);
				break;
			}
		}
		File::WriteAllLines("customers.txt", lines);
		MessageBox::Show("Password updated successfully!");
		tb_currentPassword->Text = newPassword;
		tb_newPassword->Text = "";
		tb_confirmPassword->Text = "";



		//go to current info and show a message of data is saved
		showCategoryPanel(pn_currentInfo);
	}
	private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {
		pn_resetPassword->BringToFront();
	}
	

		   //Products
    private: System::Void btn_products_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		if (btn_products != selectedButton) {
			btn_products->BackColor = Color::DimGray;
		}
	}
	private: System::Void btn_products_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (btn_products != selectedButton) {
			btn_products->BackColor = Color::Transparent;
		}
	}
	private: System::Void btn_products_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedButton = btn_products;
		showPanel(pn_products);
		pn_main_category->BringToFront();
		MenuBGColor(btn_products);
	}
    private: System::Void btn_snacks_Click(System::Object^ sender, System::EventArgs^ e) {
			   showCategoryPanel(pn_snacks_category);
    }
	private: System::Void btn_household_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_household_category);
	}
	private: System::Void btn_pet_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_pet_supplies_category);
	}
	private: System::Void btn_vegetabe_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_vegetable_category);
	}
	private: System::Void btn_dairy_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_dairy_category);
	}
	private: System::Void btn_butcher_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_butchershop_category);
	}
	private: System::Void btn_seafood_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_seafood_category);
	}
	private: System::Void btn_poultry_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_poultry_category);
	}
	private: System::Void btn_bakery_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_bakery_category);
	}
	private: System::Void btn_fruits_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_fruits_category);
	}
	
		   //Orders
	private: System::Void btn_orders_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		if (btn_orders != selectedButton) {
			btn_orders->BackColor = Color::DimGray;
		}
	}
	private: System::Void btn_orders_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (btn_orders != selectedButton) {
			btn_orders->BackColor = Color::Transparent;
		}
	}
	private: System::Void btn_orders_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedButton = btn_orders;
		showPanel(pn_orders);
		loadCurrentUserOrder();
		MenuBGColor(btn_orders);
	}
    private: System::Void deleteProductFromOrder(String^ productName) {
			if (orders[currentCustomerIndex] == nullptr) return;

			ORDER^ order = orders[currentCustomerIndex];

			int indexToRemove = -1;

			for (int i = 0; i < order->productcount; i++) {
				if (order->Products[i]->Name == productName) {
					indexToRemove = i;
					break;
				}
			}

			if (indexToRemove != -1) {
				// Update total price correctly
				order->TotalPrice -= order->Products[indexToRemove]->Price * order->Amount[indexToRemove];

				// Shift items left
				for (int i = indexToRemove; i < order->productcount - 1; i++) {
					order->Products[i] = order->Products[i + 1];
					order->Amount[i] = order->Amount[i + 1];
				}

				order->Products[order->productcount - 1] = nullptr; // Clear last product
				order->Amount[order->productcount - 1] = 0;

				order->productcount--;

				saveCurrentOrderToFile(); // Save updated cart
				loadCurrentUserOrder();   // Refresh display
			}
		}
	private: System::Void deleteButton_Click(System::Object^ sender, System::EventArgs^ e) {
		Button^ btnDelete = safe_cast<Button^>(sender);
		if (btnDelete == nullptr) return;

		String^ productName = safe_cast<String^>(btnDelete->Tag);

		if (productName != nullptr) {
			if (MessageBox::Show("Are you sure you want to delete " + productName + "?", "Confirm Delete", MessageBoxButtons::YesNo) == System::Windows::Forms::DialogResult::Yes) {
				deleteProductFromOrder(productName); // ✅ delete from memory and file
			}
		}
	}
	private: System::Void confirm_Click(System::Object^ sender, System::EventArgs^ e)
	{
		tb_date_theinvoice->Text = DateTime::Now.ToString("hh:mm tt" + "            " + "dd/MM/yyyy");

		MessageBox::Show("Order confirmed!");
		pn_viewBill->BringToFront();
		pn_viewBill->Visible = true;
		dataGridView1->Rows->Clear(); // Clear previous rows

		if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr)
			return;

		bool foundOrder = false;

		int customerID = Convert::ToInt32(customers[currentCustomerIndex]->ID);

		for each (ORDER ^ order in orders) {
			if (order != nullptr && order->CustomerID == customerID)
			{
				double totalPrice = 0.0;

				for (int i = 0; i < order->productcount; i++)
				{
					PRODUCT^ product = order->Products[i];
					double quantity = order->Amount[i];
					double unitPrice = product->Price;
					double subtotal = quantity * unitPrice;

					dataGridView1->Rows->Add(product->Name, quantity.ToString("F2"), unitPrice.ToString("F2"), subtotal.ToString("F2"));
					totalPrice += subtotal;
				}

				lb_beforevat_number->Text = " " + totalPrice + " EGP";

				double vat = 0.14;
				double dis = 0.0;
				double shipping_cost = 100.0;

				if (order->productcount > 0)
				{
					double vatAmount = totalPrice * vat;
					double discountAmount = 0.0;

					if (totalPrice > 1000)
					{
						dis = 0.1;
						shipping_cost = 0;
						discountAmount = totalPrice * dis;
					}

					double finalTotal = totalPrice + vatAmount - discountAmount + shipping_cost;

					lb_vat_number->Text = " " + vatAmount.ToString("F2") + " EGP";
					lb_discount_number->Text = " " + discountAmount.ToString("F2") + " EGP";
					lb_shipping_number->Text = " " + shipping_cost.ToString("F2") + " EGP";
					lb_total_number->Text = " " + finalTotal.ToString("F2") + " EGP";

					StreamReader^ read_invoice = gcnew StreamReader("invoice_number.txt");
					String^ line = read_invoice->ReadLine();
					read_invoice->Close();

					int read_invoice_number = Convert::ToInt32(line);
					read_invoice_number++;

					tb_invoicenumber_theinvoice->Text = read_invoice_number.ToString();
					System::IO::File::WriteAllText("invoice_number.txt", read_invoice_number.ToString());

					foundOrder = true;
					MenuBGColor(btn_TotalBill);
					pn->Visible = true;
				}
				break;
			}
		}

		if (!foundOrder)
		{
			MessageBox::Show("No products found in the order for the selected customer.");
		}
	}
		  
		   //Total Bill
    private: System::Void tb_date_theinvoice_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	e->Handled = true; // Prevent any input
    }
    private: System::Void tb_invoicenumber_theinvoice_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	e->Handled = true; // Prevent any input
    }
    private: System::Void tb_customername_theincoive_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	e->Handled = true; // Prevent any input
    }
    private: System::Void btn_print_Click(System::Object^ sender, System::EventArgs^ e) {

	printPreviewDialog1->WindowState = FormWindowState::Maximized;
	if (printPreviewDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		printDocument1->Print();
	}
    }
    private: System::Void printDocument1_PrintPage(System::Object^ sender, System::Drawing::Printing::PrintPageEventArgs^ e) {
	System::Drawing::Font^ f = gcnew System::Drawing::Font("Arial", 20, FontStyle::Bold);
	System::Drawing::Font^ qq = gcnew System::Drawing::Font("Stencil", 20, FontStyle::Bold);
	Image^ img = Image::FromFile("Logo\\Logo.jpg");

	String^ no = "#No " + tb_invoicenumber_theinvoice->Text;
	String^ date = "Date:  " + tb_date_theinvoice->Text;
	String^ customerName = "Customer Name:  " + tb_customername_theincoive->Text;
	String^ invoice = "thank you for using                              !! ";
	String^ invoice2 = " SUPERMARKO ";

	SizeF sizeno = e->Graphics->MeasureString(no, f);
	SizeF sizedate = e->Graphics->MeasureString(date, f);
	SizeF sizecustomerName = e->Graphics->MeasureString(customerName, f);
	SizeF sizeinvoice = e->Graphics->MeasureString(invoice, f);

	e->Graphics->DrawImage(img, 600.0f, 0.0f, 250.0f, 250.0f);
	e->Graphics->DrawString(no, f, Brushes::Red, (e->PageBounds.Width - sizeno.Width) / 2.0f, 50.0f);
	e->Graphics->DrawString(date, f, Brushes::Black, 20.0f, 100.0f);
	e->Graphics->DrawString(customerName, f, Brushes::Navy, 20.0f, 150.0f);
	e->Graphics->DrawString(invoice, f, Brushes::Black, (e->PageBounds.Width - sizeinvoice.Width) / 2.0f, 1030.0f);
	e->Graphics->DrawString(invoice2, qq, Brushes::Purple, 420.0f, 1030.0f);

	float y = 200.0f;
	e->Graphics->DrawRectangle(Pens::Black, 20.0f, y, e->PageBounds.Width - 40.0f, 800.0f);

	float colHeight = 60.0f;
	float col1Width = 300.0f;
	float col2Width = 150.0f + col1Width;
	float col3Width = 150.0f + col2Width;
	float col4Width = 140.0f + col3Width;

	e->Graphics->DrawLine(Pens::Black, 20.0f, y + colHeight, e->PageBounds.Width - 20.0f, y + colHeight);
	e->Graphics->DrawLine(Pens::Black, col1Width + 20.0f, y, col1Width + 20.0f, y + 800.0f);
	e->Graphics->DrawLine(Pens::Black, col2Width + 20.0f, y, col2Width + 20.0f, y + 800.0f);
	e->Graphics->DrawLine(Pens::Black, col3Width + 20.0f, y, col3Width + 20.0f, y + 800.0f);

	e->Graphics->DrawString("Product", f, Brushes::Black, 100.0f, y + 20.0f);
	e->Graphics->DrawString("Quantity", f, Brushes::Black, col1Width + 25.0f, y + 20.0f);
	e->Graphics->DrawString("Unit price", f, Brushes::Black, col2Width + 25.0f, y + 20.0f);
	e->Graphics->DrawString("Subtotal", f, Brushes::Black, col3Width + 25.0f, y + 20.0f);

	int rowHeight = 50;
	float startY = 260.0f;
	int validRowCount = 0;
	float x = 0.0f;

	for (int i = 0; i < dataGridView1->Rows->Count; i++) {
		if (dataGridView1->Rows[i]->IsNewRow)
			continue;

		String^ product = dataGridView1->Rows[i]->Cells[0]->Value->ToString();
		String^ quantity = dataGridView1->Rows[i]->Cells[1]->Value->ToString();
		String^ unitprice = dataGridView1->Rows[i]->Cells[2]->Value->ToString();
		String^ subtotal = dataGridView1->Rows[i]->Cells[3]->Value->ToString();

		float rowY = startY + (validRowCount * rowHeight);

		System::Drawing::Font^ font = gcnew System::Drawing::Font("Arial", 16, FontStyle::Regular);
		System::Drawing::Font^ ff = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);

		e->Graphics->DrawString(product, ff, Brushes::Navy, 25.0f, rowY + 15.0f);
		e->Graphics->DrawString(quantity, font, Brushes::Black, 375.0f, rowY + 15.0f);
		e->Graphics->DrawString(unitprice, font, Brushes::Black, 500.0f, rowY + 15.0f);
		e->Graphics->DrawString(subtotal, font, Brushes::Black, 625.0f, rowY + 15.0f);

		e->Graphics->DrawLine(Pens::Black, 20.0f, rowY + rowHeight, e->PageBounds.Width - 20.0f, rowY + rowHeight);

		validRowCount++;
		x = rowY;
	}

	System::Drawing::Font^ z = gcnew System::Drawing::Font("Arial", 12, FontStyle::Bold);
	System::Drawing::Font^ p = gcnew System::Drawing::Font("Arial", 16, FontStyle::Bold);
	System::Drawing::Font^ m = gcnew System::Drawing::Font("Arial", 18, FontStyle::Bold);

	e->Graphics->DrawLine(Pens::Black, 20.0f, 800.0f, e->PageBounds.Width - 20.0f, 800.0f);
	e->Graphics->DrawString(" Total(Before VAT):  ", z, Brushes::Red, 470.0f, 805.0f);
	e->Graphics->DrawString(lb_beforevat_number->Text, p, Brushes::Navy, 630.0f, 805.0f);

	e->Graphics->DrawString(" Discount Applied:   ", z, Brushes::Red, 470.0f, 840.0f);
	e->Graphics->DrawString(lb_discount_number->Text, p, Brushes::Navy, 630.0f, 840.0f);

	e->Graphics->DrawString(" VAT (14%):    ", z, Brushes::Red, 470.0f, 875.0f);
	e->Graphics->DrawString(lb_vat_number->Text, p, Brushes::Navy, 630.0f, 875.0f);

	e->Graphics->DrawString(" Shipping Cost:     ", z, Brushes::Red, 470.0f, 910.0f);
	e->Graphics->DrawString(lb_shipping_number->Text, p, Brushes::Navy, 630.0f, 910.0f);

	e->Graphics->DrawString(" Total (After VAT):      ", z, Brushes::Red, 470.0f, 945.0f);
	e->Graphics->DrawString(lb_total_number->Text, m, Brushes::Purple, 630.0f, 945.0f);
    }
	private: System::Void btn_TotalBill_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		if (btn_TotalBill != selectedButton) {
			btn_TotalBill->BackColor = Color::DimGray;
		}
	}
	private: System::Void btn_TotalBill_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		if (btn_TotalBill != selectedButton) {
			btn_TotalBill->BackColor = Color::Transparent;
		}
	}
	private: System::Void btn_TotalBill_Click(System::Object^ sender, System::EventArgs^ e) {
		selectedButton = btn_TotalBill;
		showPanel(pn_viewBill);
		MenuBGColor(btn_TotalBill);
	}
		   
		   //log out
    private: System::Void btn_logout_Click(System::Object^ sender, System::EventArgs^ e) {
		btn_orders->ForeColor = Color::White;
		btn_orders->BackColor = Color::Transparent;
		btn_TotalBill->ForeColor = Color::White;
		btn_TotalBill->BackColor = Color::Transparent;
		btn_products->ForeColor = Color::White;
		btn_products->BackColor = Color::Transparent;
		btn_edit_information->ForeColor = Color::White;
		btn_edit_information->BackColor = Color::Transparent;
		
		pn->Visible = false;
		Label^ lb = gcnew Label();
		lb->Text = "Please confirm your order";
		lb->Font = gcnew System::Drawing::Font("sign ui", 20, FontStyle::Bold);
		lb->ForeColor = System::Drawing::Color::DarkRed;
		lb->Location = System::Drawing::Point(300, 250);
		lb->AutoSize = true;
		pn_viewBill->Controls->Add(lb);

		showPanel(pn_login);
    }
		   
//--------------------------------------------pn_default---------------------------------------------
		   //handle functions& save and load files
	private: System::Void saveCurrentOrderToFile() {
		if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr) return;

		try {
			ORDER^ order = orders[currentCustomerIndex];
			if (order == nullptr || order->productcount == 0) {
				// If no products left, clear the file (optional: or just remove that user's data)
				File::WriteAllText("order.txt", "");
				return;
			}

			String^ newLine = order->CustomerID.ToString() + "|";

			for (int i = 0; i < order->productcount; i++) {
				String^ productName = order->Products[i]->Name;
				double qty = order->Amount[i];
				double unitPrice = order->Products[i]->Price;

				newLine += productName + "," + qty.ToString("F2") + "," + unitPrice.ToString("F2");

				if (i < order->productcount - 1)
					newLine += ";"; // add separator if not last
			}

			newLine += "|" + order->TotalPrice.ToString("F2");

			// Read the current file content
			array<String^>^ lines = File::ReadAllLines("order.txt");
			bool customerFound = false;
			String^ updatedContent = "";

			// Iterate through the existing lines to check if this customer exists
			for each (String ^ line in lines) {
				array<String^>^ parts = line->Split('|');
				if (parts->Length < 3) continue;

				int fileCustomerID = Convert::ToInt32(parts[0]->Trim());

				if (fileCustomerID == order->CustomerID) {
					// Update the existing customer's order
					updatedContent += newLine + Environment::NewLine;
					customerFound = true;
				}
				else {
					// Keep the other customers' data
					updatedContent += line + Environment::NewLine;
				}
			}

			// If the customer wasn't found, add new order data for this customer
			if (!customerFound) {
				updatedContent += newLine + Environment::NewLine;
			}

			// Write the updated content to the file
			File::WriteAllText("order.txt", updatedContent);
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error saving order: " + ex->Message);
		}
	}
	private: System::Void loadCurrentUserOrder() {
		if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr)
			return;

		try {
			orderList->Controls->Clear(); // Clear previous order items
			array<String^>^ lines = File::ReadAllLines("order.txt");

			bool foundOrder = false;


			for each (String ^ line in lines) {
				array<String^>^ parts = line->Split('|');

				if (parts->Length < 3) continue;

				int fileCustomerID = Convert::ToInt32(parts[0]->Trim());

				if (fileCustomerID == customers[currentCustomerIndex]->ID) {
					foundOrder = true;

					String^ productsPart = parts[1];
					double totalPrice = Convert::ToDouble(parts[2]);

					// Fill order memory
					orders[currentCustomerIndex] = gcnew ORDER();
					orders[currentCustomerIndex]->CustomerID = fileCustomerID;
					orders[currentCustomerIndex]->TotalPrice = totalPrice;
					orders[currentCustomerIndex]->productcount = 0;

					array<String^>^ productEntries = productsPart->Split(';');

					for each (String ^ productEntry in productEntries) {
						if (String::IsNullOrWhiteSpace(productEntry)) continue;

						array<String^>^ prodParts = productEntry->Split(',');

						String^ productName = prodParts[0]->Trim();
						double qty = Convert::ToDouble(prodParts[1]);
						double unitPrice = Convert::ToDouble(prodParts[2]);

						PRODUCT^ product = gcnew PRODUCT();
						product->Name = productName;
						product->Price = unitPrice;

						int idx = orders[currentCustomerIndex]->productcount;
						orders[currentCustomerIndex]->Products[idx] = product;
						orders[currentCustomerIndex]->Amount[idx] = qty;
						orders[currentCustomerIndex]->productcount++;

						// === Create UI for product ===
						Panel^ itemPanel = gcnew Panel();
						itemPanel->Height = 120;
						itemPanel->Width = 875;
						itemPanel->BackColor = Color::White;
						itemPanel->Margin = System::Windows::Forms::Padding(10);

						// ✨ Save product name inside Tag
						itemPanel->Tag = productName;

						PictureBox^ productImage = gcnew PictureBox();
						productImage->Size = Drawing::Size(100, 100);
						productImage->Location = Point(10, 10);
						productImage->SizeMode = PictureBoxSizeMode::Zoom;

						String^ cleanName = productName->Replace(" ", "_")->Replace("(", "")->Replace(")", "")->Replace("\"", "")->Trim();
						String^ imagePath = "images\\" + cleanName + ".jpg";

						try {
							if (File::Exists(imagePath)) {
								productImage->Image = Image::FromFile(imagePath);
							}
							else {
								productImage->Image = Image::FromFile("images\\placeholder.jpg");
							}
						}
						catch (...) {
							productImage->Image = Image::FromFile("images\\placeholder.jpg");
						}

						itemPanel->Controls->Add(productImage);

						Label^ lblInfo = gcnew Label();
						lblInfo->Text = "Product: " + productName + "\nQuantity: " + qty.ToString("F2") +
							"\nUnit Price: " + unitPrice.ToString("F2") + " EGP\nTotal: " +
							(qty * unitPrice).ToString("F2") + " EGP";
						lblInfo->Location = Point(130, 20);
						lblInfo->Width = 450;
						lblInfo->Height = 80;
						lblInfo->Font = gcnew Drawing::Font("Segoe UI", 12);
						itemPanel->Controls->Add(lblInfo);

						Button^ btnDelete = gcnew Button();
						btnDelete->Text = "Delete";
						btnDelete->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
						btnDelete->Width = 100;
						btnDelete->Height = 40;
						btnDelete->BackColor = Color::FromArgb(220, 20, 60);
						btnDelete->ForeColor = Color::White;
						btnDelete->Location = Point(750, 60);
						btnDelete->Tag = productName;
						btnDelete->Click += gcnew EventHandler(this, &MyForm::deleteButton_Click);
						itemPanel->Controls->Add(btnDelete);

						Button^ btnModify = gcnew Button();
						btnModify->Text = "Modify";
						btnModify->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
						btnModify->Width = 100;
						btnModify->Height = 40;
						btnModify->BackColor = Color::FromArgb(30, 144, 255);
						btnModify->ForeColor = Color::White;
						btnModify->Location = Point(750, 20);
						btnModify->Click += gcnew EventHandler(this, &MyForm::handleModifyQuantityClick);
						itemPanel->Controls->Add(btnModify);

						orderList->Controls->Add(itemPanel);
					}

					// === Add Total Price Label ===
					Label^ lblTotal = gcnew Label();
					lblTotal->Text = "TOTAL ORDER: " + totalPrice.ToString("F2") + " EGP";
					lblTotal->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
					lblTotal->ForeColor = Color::DarkGreen;
					lblTotal->Width = 800;
					lblTotal->Height = 40;
					lblTotal->TextAlign = ContentAlignment::MiddleCenter;
					orderList->Controls->Add(lblTotal);

					//panel to show the order is confirmed
					Panel^ pnConfirmed = gcnew Panel();
					pnConfirmed->Width = 800;
					pnConfirmed->Height = 100;

					orderList->Controls->Add(pnConfirmed);

					//add button to Click here to confirm
					Button^ confirm = gcnew Button();
					confirm->Text = "Click here to confirm";
					confirm->Width = 250;
					confirm->Height = 45;
					confirm->BackColor = Color::FromArgb(220, 20, 60);
					confirm->ForeColor = Color::Black;
					confirm->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
					confirm->TextAlign = ContentAlignment::MiddleCenter;
					confirm->Location = Point(
						(pnConfirmed->Width - confirm->Width) / 2,
						(pnConfirmed->Height - confirm->Height) / 2
					);

					pnConfirmed->Controls->Add(confirm);
					confirm->Click += gcnew EventHandler(this, &MyForm::confirm_Click);

					break; // 🛑 Exit after finding order
				}
			}

			if (!foundOrder) {
				// No order found
				Label^ lblNoOrder = gcnew Label();
				lblNoOrder->Text = "No orders found.";
				lblNoOrder->Font = gcnew Drawing::Font("Segoe UI", 18, FontStyle::Bold);
				lblNoOrder->ForeColor = Color::Gray;
				lblNoOrder->Dock = DockStyle::Top;
				lblNoOrder->Width = 892;
				lblNoOrder->Height = 50;
				lblNoOrder->TextAlign = ContentAlignment::MiddleCenter;
				orderList->Controls->Add(lblNoOrder);
			}
		}
		catch (Exception^ ex) {
			MessageBox::Show("Error loading order: " + ex->Message);
		}
	}
	private: System::Void handleModifyQuantityClick(System::Object^ sender, System::EventArgs^ e) {
		Button^ modifyButton = safe_cast<Button^>(sender);
		Panel^ parentPanel = safe_cast<Panel^>(modifyButton->Parent);

		String^ productName = safe_cast<String^>(parentPanel->Tag);

		if (String::IsNullOrEmpty(productName)) {
			MessageBox::Show("Product not found.");
			return;
		}

		Form^ quantityForm = gcnew Form();
		quantityForm->Text = "Modify Quantity - " + productName;
		quantityForm->Width = 300;
		quantityForm->Height = 180;
		quantityForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		quantityForm->StartPosition = FormStartPosition::CenterScreen;

		Label^ lbl = gcnew Label();
		lbl->Text = "Enter new quantity:";
		lbl->Location = Point(30, 20);
		lbl->Width = 200;
		quantityForm->Controls->Add(lbl);

		NumericUpDown^ numericQuantity = gcnew NumericUpDown();
		numericQuantity->Location = Point(30, 50);
		numericQuantity->Width = 200;
		numericQuantity->Minimum = 1;
		numericQuantity->Maximum = 10000;
		numericQuantity->Value = 1;
		numericQuantity->DecimalPlaces = 0;
		quantityForm->Controls->Add(numericQuantity);

		Button^ btnOk = gcnew Button();
		btnOk->Text = "OK";
		btnOk->Location = Point(30, 90);
		btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
		quantityForm->Controls->Add(btnOk);

		Button^ btnCancel = gcnew Button();
		btnCancel->Text = "Cancel";
		btnCancel->Location = Point(160, 90);
		btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		quantityForm->Controls->Add(btnCancel);

		if (quantityForm->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			int newQuantity = (int)numericQuantity->Value;

			if (newQuantity <= 0) {
				MessageBox::Show("Quantity must be greater than 0.");
				return;
			}

			bool found = false;
			for (int i = 0; i < orders[currentCustomerIndex]->productcount; i++) {
				if (orders[currentCustomerIndex]->Products[i]->Name == productName) {
					orders[currentCustomerIndex]->Amount[i] = newQuantity;
					found = true;
					break;
				}
			}

			if (!found) {
				MessageBox::Show("Product not found in memory.");
				return;
			}

			// Save updated order back to file
			try {
				array<String^>^ allLines = File::ReadAllLines("order.txt");

				for (int i = 0; i < allLines->Length; i++) {
					array<String^>^ parts = allLines[i]->Split('|');
					if (parts->Length < 3) continue;

					int fileCustomerID = Convert::ToInt32(parts[0]->Trim());

					if (fileCustomerID == customers[currentCustomerIndex]->ID) {
						String^ newProductPart = "";
						for (int j = 0; j < orders[currentCustomerIndex]->productcount; j++) {
							String^ name = orders[currentCustomerIndex]->Products[j]->Name;
							double qty = orders[currentCustomerIndex]->Amount[j];
							double unitPrice = orders[currentCustomerIndex]->Products[j]->Price;
							newProductPart += name + "," + qty.ToString("F2") + "," + unitPrice.ToString("F2") + ";";
						}

						double newTotal = 0;
						for (int j = 0; j < orders[currentCustomerIndex]->productcount; j++) {
							newTotal += orders[currentCustomerIndex]->Amount[j] * orders[currentCustomerIndex]->Products[j]->Price;
						}

						allLines[i] = fileCustomerID.ToString() + "|" + newProductPart + "|" + newTotal.ToString("F2");
						break;
					}
				}

				File::WriteAllLines("order.txt", allLines);
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error saving updated order: " + ex->Message);
			}

			MessageBox::Show("Quantity updated successfully!");
			loadCurrentUserOrder(); // Reload updated order
		}
	}
	private: void CreateQuantityForm(String^ productName)
	{
		Form^ quantityForm = gcnew Form();
		quantityForm->Text = "Modify Quantity - " + productName;
		quantityForm->Width = 300;
		quantityForm->Height = 180;
		quantityForm->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
		quantityForm->StartPosition = FormStartPosition::CenterScreen;

		Label^ lbl = gcnew Label();
		lbl->Text = "Enter new quantity:";
		lbl->Location = Point(30, 20);
		lbl->Width = 200;
		quantityForm->Controls->Add(lbl);

		NumericUpDown^ numericQuantity = gcnew NumericUpDown();
		numericQuantity->Location = Point(30, 50);
		numericQuantity->Width = 200;
		numericQuantity->Minimum = 1;
		numericQuantity->Maximum = 10000;
		numericQuantity->Value = 1;
		numericQuantity->DecimalPlaces = 0;
		quantityForm->Controls->Add(numericQuantity);

		Button^ btnOk = gcnew Button();
		btnOk->Text = "OK";
		btnOk->Location = Point(30, 90);
		btnOk->DialogResult = System::Windows::Forms::DialogResult::OK;
		quantityForm->Controls->Add(btnOk);

		Button^ btnCancel = gcnew Button();
		btnCancel->Text = "Cancel";
		btnCancel->Location = Point(160, 90);
		btnCancel->DialogResult = System::Windows::Forms::DialogResult::Cancel;
		quantityForm->Controls->Add(btnCancel);

		// Show the form as a dialog
		if (quantityForm->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			int selectedQuantity = (int)numericQuantity->Value;
			
		}
	}
    private: System::Void handleAddToCart(System::Object^ sender, System::EventArgs^ e) {
	  if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr) {
		  MessageBox::Show("You must be logged in to add items to the cart.");
		  return;
	  }

	  Button^ clickedButton = safe_cast<Button^>(sender);
	  if (clickedButton == nullptr || clickedButton->Parent == nullptr) return;

	  FlowLayoutPanel^ productPanel = safe_cast<FlowLayoutPanel^>(clickedButton->Parent);
	  if (productPanel == nullptr) return;

	  // Find product info
	  String^ productName = "";
	  double quantity = 0;
	  double price = 0;

	  for each (Control ^ control in productPanel->Controls) {
		  Label^ lbl = dynamic_cast<Label^>(control);
		  if (lbl != nullptr) {
			  if (lbl->Text->StartsWith("Name: ")) {
				  productName = lbl->Text->Substring(6)->Trim();
			  }
			  else if (lbl->Text->StartsWith("Price: ")) {
				  String^ priceText = lbl->Text->Substring(7)->Replace("EGP", "")->Trim();
				  price = Convert::ToDouble(priceText);
			  }
		  }

		  NumericUpDown^ quantityBox = dynamic_cast<NumericUpDown^>(control);
		  if (quantityBox != nullptr) {
			  quantity = (double)quantityBox->Value;
		  }

		  Panel^ panel = dynamic_cast<Panel^>(control);
		  if (panel != nullptr) {
			  for each (Control ^ insideCtrl in panel->Controls) {
				  NumericUpDown^ qtyInside = dynamic_cast<NumericUpDown^>(insideCtrl);
				  if (qtyInside != nullptr) {
					  quantity = (double)qtyInside->Value;
				  }
			  }
		  }
	  }

	  if (productName == "" || quantity <= 0) {
		  MessageBox::Show("Please select a quantity greater than 0.");
		  return;
	  }

	  // Find the product in products array
	  PRODUCT^ selectedProduct = nullptr;
	  for (int cat = 0; cat < numOfCategories; cat++) {
		  for (int i = 0; i < productCounts[cat]; i++) {
			  if (products[cat][i]->Name == productName) {
				  selectedProduct = products[cat][i];
				  break;
			  }
		  }
		  if (selectedProduct != nullptr) break;
	  }

	  if (selectedProduct == nullptr) {
		  MessageBox::Show("Product not found.");
		  return;
	  }

	  // Initialize user's order if needed
	  if (orders[currentCustomerIndex] == nullptr) {
		  orders[currentCustomerIndex] = gcnew ORDER();
		  orders[currentCustomerIndex]->CustomerID = customers[currentCustomerIndex]->ID;
		  orders[currentCustomerIndex]->productcount = 0;
	  }

	  ORDER^ order = orders[currentCustomerIndex];

	  if (order->productcount >= numOfProducts) {
		  MessageBox::Show("Cart is full.");
		  return;
	  }

	  // === NEW SMART LOGIC ===
	  bool productUpdated = false;
	  double oldProductTotal = 0.0;

	  for (int i = 0; i < order->productcount; i++) {
		  if (order->Products[i]->Name == productName) {
			  // Product exists -> update quantity and price
			  oldProductTotal = order->Products[i]->Price * order->Amount[i];
			  order->Amount[i] = quantity; // Update quantity
			  order->Products[i]->Price = selectedProduct->Price; // Update price (if changed)
			  productUpdated = true;
			  break;
		  }
	  }

	  if (!productUpdated) {
		  // Product does not exist -> add new
		  int idx = order->productcount;
		  order->Products[idx] = selectedProduct;
		  order->Amount[idx] = quantity;
		  order->productcount++;
	  }

	  // Update total price
	  order->TotalPrice = 0.0;
	  for (int i = 0; i < order->productcount; i++) {
		  order->TotalPrice += order->Products[i]->Price * order->Amount[i];
	  }

	  MessageBox::Show(productName + (productUpdated ? " updated!" : " added!") + " to your cart!");

	  // Save the updated order
	  saveCurrentOrderToFile();
  }

private: System::Void btn_editInfo_Click(System::Object^ sender, System::EventArgs^ e) {
	showCategoryPanel(pn_editInfo);
}
};
}

