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
	using namespace IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>

	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
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
				btnBack->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
					static_cast<System::Byte>(0)));
				btnBack->Height = 50;
				btnBack->BackColor = Color::FromArgb(230, 52, 98);
				btnBack->ForeColor = Color::White;
				btnBack->FlatStyle = FlatStyle::Flat;
				btnBack->Click += gcnew EventHandler(this, &MyForm::handleBackToCategories);

				Panel^ pn_back = gcnew Panel();
				pn_back->Width = 750;
				pn_back->Height = 50;
				pn_back->BackColor = Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
					static_cast<System::Int32>(static_cast<System::Byte>(239)));
				pn_back->Controls->Add(btnBack);

				panelToFill->Controls->Add(pn_back); // 🔥 Add it before the product cards

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
					btnAdd->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
						static_cast<System::Byte>(0)));
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
	private: System::Windows::Forms::PictureBox^ thankyou;
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
	private: System::Windows::Forms::LinkLabel^ link_login;
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
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Timer^ timerforexit;
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
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->btn_exit = (gcnew System::Windows::Forms::Button());
			this->welcomeScreen = (gcnew System::Windows::Forms::PictureBox());
			this->pn_defualt = (gcnew System::Windows::Forms::Panel());
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
			this->pn_viewBill = (gcnew System::Windows::Forms::Panel());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->pn_edit_information = (gcnew System::Windows::Forms::Panel());
			this->pn_currentInfo = (gcnew System::Windows::Forms::Panel());
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
			this->pn_resetPassword = (gcnew System::Windows::Forms::Panel());
			this->tb_confirmPassword = (gcnew System::Windows::Forms::TextBox());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->btn_saveResetPassword = (gcnew System::Windows::Forms::Button());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->tb_newPassword = (gcnew System::Windows::Forms::TextBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->pn_editInfo = (gcnew System::Windows::Forms::Panel());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->btn_cancelEdit = (gcnew System::Windows::Forms::Button());
			this->btn_saveEdit = (gcnew System::Windows::Forms::Button());
			this->tb_edit_phonenumber = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->tb_edit_location = (gcnew System::Windows::Forms::TextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tb_edit_username = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pn_blank = (gcnew System::Windows::Forms::Panel());
			this->pb_blankpicutre = (gcnew System::Windows::Forms::PictureBox());
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
			this->pn_login = (gcnew System::Windows::Forms::Panel());
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
			this->pn_register = (gcnew System::Windows::Forms::Panel());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btn_refresh_location_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_phonenumber_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_password_register = (gcnew System::Windows::Forms::Button());
			this->btn_refresh_username_register = (gcnew System::Windows::Forms::Button());
			this->btn_seepassword = (gcnew System::Windows::Forms::Button());
			this->link_login = (gcnew System::Windows::Forms::LinkLabel());
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
			this->thankyou = (gcnew System::Windows::Forms::PictureBox());
			this->timerforexit = (gcnew System::Windows::Forms::Timer(this->components));
			this->pn_upper_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->BeginInit();
			this->pn_main_dashboard->SuspendLayout();
			this->pn_start->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->BeginInit();
			this->pn_defualt->SuspendLayout();
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
			this->pn_edit_information->SuspendLayout();
			this->pn_currentInfo->SuspendLayout();
			this->pn_resetPassword->SuspendLayout();
			this->pn_editInfo->SuspendLayout();
			this->pn_blank->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->BeginInit();
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_picture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->BeginInit();
			this->pn_login->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->pn_register->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->pn_thankyou->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thankyou))->BeginInit();
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
			this->pn_upper_bar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_upper_bar_Paint);
			// 
			// lb_brand_name
			// 
			this->lb_brand_name->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_brand_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->lb_brand_name->Location = System::Drawing::Point(76, 6);
			this->lb_brand_name->Name = L"lb_brand_name";
			this->lb_brand_name->Size = System::Drawing::Size(251, 43);
			this->lb_brand_name->TabIndex = 4;
			this->lb_brand_name->Text = L"SUPERMARKO";
			this->lb_brand_name->Click += gcnew System::EventHandler(this, &MyForm::lb_brand_name_Click);
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
			this->pb_icon->Click += gcnew System::EventHandler(this, &MyForm::pb_icon_Click);
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
			this->btn_minimize->MouseHover += gcnew System::EventHandler(this, &MyForm::btn_minimize_MouseHover);
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
			this->pn_main_dashboard->Controls->Add(this->pn_start);
			this->pn_main_dashboard->Controls->Add(this->pn_defualt);
			this->pn_main_dashboard->Controls->Add(this->pn_login);
			this->pn_main_dashboard->Controls->Add(this->pn_register);
			this->pn_main_dashboard->Controls->Add(this->pn_thankyou);
			this->pn_main_dashboard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_dashboard->Location = System::Drawing::Point(0, 55);
			this->pn_main_dashboard->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_main_dashboard->Name = L"pn_main_dashboard";
			this->pn_main_dashboard->Size = System::Drawing::Size(1485, 745);
			this->pn_main_dashboard->TabIndex = 1;
			this->pn_main_dashboard->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_main_dashboard_Paint);
			// 
			// pn_start
			// 
			this->pn_start->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_start->Controls->Add(this->btn_start);
			this->pn_start->Controls->Add(this->btn_exit);
			this->pn_start->Controls->Add(this->welcomeScreen);
			this->pn_start->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_start->Location = System::Drawing::Point(0, 0);
			this->pn_start->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_start->Name = L"pn_start";
			this->pn_start->Size = System::Drawing::Size(1485, 745);
			this->pn_start->TabIndex = 3;
			this->pn_start->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_start_Paint);
			// 
			// btn_start
			// 
			this->btn_start->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_start->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->btn_start->FlatAppearance->BorderSize = 0;
			this->btn_start->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_start->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_start->Location = System::Drawing::Point(635, 474);
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
			this->btn_exit->FlatAppearance->BorderSize = 0;
			this->btn_exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_exit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_exit->Location = System::Drawing::Point(635, 549);
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
			this->welcomeScreen->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->welcomeScreen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"welcomeScreen.Image")));
			this->welcomeScreen->Location = System::Drawing::Point(0, 0);
			this->welcomeScreen->Margin = System::Windows::Forms::Padding(4);
			this->welcomeScreen->Name = L"welcomeScreen";
			this->welcomeScreen->Size = System::Drawing::Size(1500, 745);
			this->welcomeScreen->TabIndex = 2;
			this->welcomeScreen->TabStop = false;
			this->welcomeScreen->Click += gcnew System::EventHandler(this, &MyForm::welcomeScreen_Click_1);
			// 
			// pn_defualt
			// 
			this->pn_defualt->Controls->Add(this->pn_products);
			this->pn_defualt->Controls->Add(this->pn_orders);
			this->pn_defualt->Controls->Add(this->pn_viewBill);
			this->pn_defualt->Controls->Add(this->pn_edit_information);
			this->pn_defualt->Controls->Add(this->pn_blank);
			this->pn_defualt->Controls->Add(this->pn_left_bar);
			this->pn_defualt->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_defualt->Location = System::Drawing::Point(0, 0);
			this->pn_defualt->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_defualt->Name = L"pn_defualt";
			this->pn_defualt->Size = System::Drawing::Size(1485, 745);
			this->pn_defualt->TabIndex = 4;
			this->pn_defualt->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_defualt_Paint);
			// 
			// pn_products
			// 
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
			this->pn_products->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_products_Paint);
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
			this->pn_main_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_main_category_Paint);
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
			this->flowLayoutPanel2->Size = System::Drawing::Size(1193, 597);
			this->flowLayoutPanel2->TabIndex = 0;
			this->flowLayoutPanel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::flowLayoutPanel2_Paint);
			// 
			// btn_fruits
			// 
			this->btn_fruits->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_fruits->FlatAppearance->BorderSize = 0;
			this->btn_fruits->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_fruits->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_fruits->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_fruits.Image")));
			this->btn_fruits->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_fruits->Location = System::Drawing::Point(7, 7);
			this->btn_fruits->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_fruits->Name = L"btn_fruits";
			this->btn_fruits->Size = System::Drawing::Size(573, 135);
			this->btn_fruits->TabIndex = 0;
			this->btn_fruits->Text = L"Fresh Produce(fruits)";
			this->btn_fruits->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_fruits->UseVisualStyleBackColor = false;
			this->btn_fruits->Click += gcnew System::EventHandler(this, &MyForm::btn_fruits_Click);
			// 
			// btn_vegetabe
			// 
			this->btn_vegetabe->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_vegetabe->FlatAppearance->BorderSize = 0;
			this->btn_vegetabe->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_vegetabe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_vegetabe->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_vegetabe.Image")));
			this->btn_vegetabe->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_vegetabe->Location = System::Drawing::Point(592, 7);
			this->btn_vegetabe->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_vegetabe->Name = L"btn_vegetabe";
			this->btn_vegetabe->Size = System::Drawing::Size(573, 135);
			this->btn_vegetabe->TabIndex = 1;
			this->btn_vegetabe->Text = L"Fresh Produce(vegetables) ";
			this->btn_vegetabe->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_vegetabe->UseVisualStyleBackColor = false;
			this->btn_vegetabe->Click += gcnew System::EventHandler(this, &MyForm::btn_vegetabe_Click);
			// 
			// btn_dairy
			// 
			this->btn_dairy->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_dairy->FlatAppearance->BorderSize = 0;
			this->btn_dairy->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_dairy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_dairy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_dairy.Image")));
			this->btn_dairy->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_dairy->Location = System::Drawing::Point(7, 154);
			this->btn_dairy->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_dairy->Name = L"btn_dairy";
			this->btn_dairy->Size = System::Drawing::Size(573, 135);
			this->btn_dairy->TabIndex = 2;
			this->btn_dairy->Text = L"Dairy and Eggs";
			this->btn_dairy->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_dairy->UseVisualStyleBackColor = false;
			this->btn_dairy->Click += gcnew System::EventHandler(this, &MyForm::btn_dairy_Click);
			// 
			// btn_butcher
			// 
			this->btn_butcher->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_butcher->FlatAppearance->BorderSize = 0;
			this->btn_butcher->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_butcher->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_butcher->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_butcher.Image")));
			this->btn_butcher->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_butcher->Location = System::Drawing::Point(592, 154);
			this->btn_butcher->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_butcher->Name = L"btn_butcher";
			this->btn_butcher->Size = System::Drawing::Size(573, 135);
			this->btn_butcher->TabIndex = 3;
			this->btn_butcher->Text = L"Bucher shop";
			this->btn_butcher->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_butcher->UseVisualStyleBackColor = false;
			this->btn_butcher->Click += gcnew System::EventHandler(this, &MyForm::btn_butcher_Click);
			// 
			// btn_seafood
			// 
			this->btn_seafood->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_seafood->FlatAppearance->BorderSize = 0;
			this->btn_seafood->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seafood->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_seafood->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seafood.Image")));
			this->btn_seafood->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_seafood->Location = System::Drawing::Point(7, 301);
			this->btn_seafood->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_seafood->Name = L"btn_seafood";
			this->btn_seafood->Size = System::Drawing::Size(573, 135);
			this->btn_seafood->TabIndex = 4;
			this->btn_seafood->Text = L"Seafood";
			this->btn_seafood->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_seafood->UseVisualStyleBackColor = false;
			this->btn_seafood->Click += gcnew System::EventHandler(this, &MyForm::btn_seafood_Click);
			// 
			// btn_poultry
			// 
			this->btn_poultry->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_poultry->FlatAppearance->BorderSize = 0;
			this->btn_poultry->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_poultry->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_poultry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_poultry.Image")));
			this->btn_poultry->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_poultry->Location = System::Drawing::Point(592, 301);
			this->btn_poultry->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_poultry->Name = L"btn_poultry";
			this->btn_poultry->Size = System::Drawing::Size(573, 135);
			this->btn_poultry->TabIndex = 5;
			this->btn_poultry->Text = L"Poultry";
			this->btn_poultry->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_poultry->UseVisualStyleBackColor = false;
			this->btn_poultry->Click += gcnew System::EventHandler(this, &MyForm::btn_poultry_Click);
			// 
			// btn_bakery
			// 
			this->btn_bakery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_bakery->FlatAppearance->BorderSize = 0;
			this->btn_bakery->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_bakery->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_bakery->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_bakery.Image")));
			this->btn_bakery->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_bakery->Location = System::Drawing::Point(7, 448);
			this->btn_bakery->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_bakery->Name = L"btn_bakery";
			this->btn_bakery->Size = System::Drawing::Size(573, 135);
			this->btn_bakery->TabIndex = 6;
			this->btn_bakery->Text = L"Bakery and Bread";
			this->btn_bakery->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_bakery->UseVisualStyleBackColor = false;
			this->btn_bakery->Click += gcnew System::EventHandler(this, &MyForm::btn_bakery_Click);
			// 
			// btn_snacks
			// 
			this->btn_snacks->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_snacks->FlatAppearance->BorderSize = 0;
			this->btn_snacks->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_snacks->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_snacks->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_snacks.Image")));
			this->btn_snacks->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_snacks->Location = System::Drawing::Point(592, 448);
			this->btn_snacks->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_snacks->Name = L"btn_snacks";
			this->btn_snacks->Size = System::Drawing::Size(573, 135);
			this->btn_snacks->TabIndex = 7;
			this->btn_snacks->Text = L"Snacks and Sweets";
			this->btn_snacks->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_snacks->UseVisualStyleBackColor = false;
			this->btn_snacks->Click += gcnew System::EventHandler(this, &MyForm::btn_snacks_Click);
			// 
			// btn_household
			// 
			this->btn_household->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_household->FlatAppearance->BorderSize = 0;
			this->btn_household->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_household->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_household->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_household.Image")));
			this->btn_household->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_household->Location = System::Drawing::Point(7, 595);
			this->btn_household->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_household->Name = L"btn_household";
			this->btn_household->Size = System::Drawing::Size(573, 135);
			this->btn_household->TabIndex = 8;
			this->btn_household->Text = L"Household and Cleaning supplies";
			this->btn_household->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_household->UseVisualStyleBackColor = false;
			this->btn_household->Click += gcnew System::EventHandler(this, &MyForm::btn_household_Click);
			// 
			// btn_pet
			// 
			this->btn_pet->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_pet->FlatAppearance->BorderSize = 0;
			this->btn_pet->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_pet->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_pet->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_pet.Image")));
			this->btn_pet->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_pet->Location = System::Drawing::Point(592, 595);
			this->btn_pet->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_pet->Name = L"btn_pet";
			this->btn_pet->Size = System::Drawing::Size(573, 135);
			this->btn_pet->TabIndex = 9;
			this->btn_pet->Text = L"Pet Supplies";
			this->btn_pet->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
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
			this->pn_pet_supplies_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_pet_supplies_category_Paint);
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
			this->pn_household_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_household_category_Paint);
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
			this->pn_snacks_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_snacks_category_Paint);
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
			this->pn_bakery_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_bakery_category_Paint);
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
			this->pn_poultry_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_poultry_category_Paint);
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
			this->pn_seafood_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_seafood_category_Paint);
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
			this->pn_butchershop_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_butchershop_category_Paint);
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
			this->pn_dairy_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_dairy_category_Paint);
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
			this->pn_vegetable_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_vegetable_category_Paint);
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
			this->pn_fruits_category->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_fruits_category_Paint);
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
			this->pn_orders->Controls->Add(this->label19);
			this->pn_orders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_orders->Location = System::Drawing::Point(296, 0);
			this->pn_orders->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_orders->Name = L"pn_orders";
			this->pn_orders->Size = System::Drawing::Size(1189, 745);
			this->pn_orders->TabIndex = 3;
			this->pn_orders->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_orders_Paint);
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
			// pn_viewBill
			// 
			this->pn_viewBill->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_viewBill->Controls->Add(this->label18);
			this->pn_viewBill->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_viewBill->Location = System::Drawing::Point(296, 0);
			this->pn_viewBill->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_viewBill->Name = L"pn_viewBill";
			this->pn_viewBill->Size = System::Drawing::Size(1189, 745);
			this->pn_viewBill->TabIndex = 5;
			// 
			// label18
			// 
			this->label18->Dock = System::Windows::Forms::DockStyle::Top;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label18->Location = System::Drawing::Point(0, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(1189, 148);
			this->label18->TabIndex = 1;
			this->label18->Text = L"Total Bill";
			this->label18->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pn_edit_information
			// 
			this->pn_edit_information->Anchor = System::Windows::Forms::AnchorStyles::Top;
			this->pn_edit_information->Controls->Add(this->pn_currentInfo);
			this->pn_edit_information->Controls->Add(this->pn_resetPassword);
			this->pn_edit_information->Controls->Add(this->pn_editInfo);
			this->pn_edit_information->Controls->Add(this->label1);
			this->pn_edit_information->Location = System::Drawing::Point(289, 0);
			this->pn_edit_information->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_edit_information->Name = L"pn_edit_information";
			this->pn_edit_information->Size = System::Drawing::Size(1204, 745);
			this->pn_edit_information->TabIndex = 1;
			this->pn_edit_information->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_edit_information_Paint);
			// 
			// pn_currentInfo
			// 
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
			this->pn_currentInfo->Location = System::Drawing::Point(0, 148);
			this->pn_currentInfo->Margin = System::Windows::Forms::Padding(4);
			this->pn_currentInfo->Name = L"pn_currentInfo";
			this->pn_currentInfo->Size = System::Drawing::Size(1204, 597);
			this->pn_currentInfo->TabIndex = 1;
			// 
			// btn_seepassword_editinfo
			// 
			this->btn_seepassword_editinfo->BackColor = System::Drawing::SystemColors::Control;
			this->btn_seepassword_editinfo->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepassword_editinfo.BackgroundImage")));
			this->btn_seepassword_editinfo->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepassword_editinfo->FlatAppearance->BorderSize = 0;
			this->btn_seepassword_editinfo->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepassword_editinfo->Location = System::Drawing::Point(927, 316);
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
			this->btn_reset->Location = System::Drawing::Point(536, 416);
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
			this->label16->Location = System::Drawing::Point(444, 14);
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
			this->btn_editInfo->Location = System::Drawing::Point(364, 416);
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
			this->tb_currentPassword->Location = System::Drawing::Point(568, 304);
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
			this->label8->Location = System::Drawing::Point(273, 302);
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
			this->tb_currentPhoneNumber->Location = System::Drawing::Point(568, 167);
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
			this->label7->Location = System::Drawing::Point(273, 164);
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
			this->tb_currentLocation->Location = System::Drawing::Point(568, 238);
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
			this->label6->Location = System::Drawing::Point(273, 235);
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
			this->tb_currentUsername->Location = System::Drawing::Point(568, 103);
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
			this->label5->Location = System::Drawing::Point(273, 97);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(164, 41);
			this->label5->TabIndex = 0;
			this->label5->Text = L"UserName";
			// 
			// pn_resetPassword
			// 
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
			this->pn_resetPassword->Location = System::Drawing::Point(0, 148);
			this->pn_resetPassword->Margin = System::Windows::Forms::Padding(4);
			this->pn_resetPassword->Name = L"pn_resetPassword";
			this->pn_resetPassword->Size = System::Drawing::Size(1204, 597);
			this->pn_resetPassword->TabIndex = 2;
			// 
			// tb_confirmPassword
			// 
			this->tb_confirmPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_confirmPassword->Location = System::Drawing::Point(591, 241);
			this->tb_confirmPassword->Margin = System::Windows::Forms::Padding(4);
			this->tb_confirmPassword->Name = L"tb_confirmPassword";
			this->tb_confirmPassword->PasswordChar = '*';
			this->tb_confirmPassword->Size = System::Drawing::Size(333, 42);
			this->tb_confirmPassword->TabIndex = 22;
			this->tb_confirmPassword->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_confirmPassword_TextChanged);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label17->Location = System::Drawing::Point(273, 246);
			this->label17->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(273, 41);
			this->label17->TabIndex = 21;
			this->label17->Text = L"Confirm Password";
			this->label17->Click += gcnew System::EventHandler(this, &MyForm::label17_Click);
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(469, 21);
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
			this->button2->Location = System::Drawing::Point(584, 348);
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
			this->btn_saveResetPassword->Location = System::Drawing::Point(420, 348);
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
			this->textBox8->Location = System::Drawing::Point(589, 107);
			this->textBox8->Margin = System::Windows::Forms::Padding(4);
			this->textBox8->Name = L"textBox8";
			this->textBox8->ReadOnly = true;
			this->textBox8->Size = System::Drawing::Size(333, 42);
			this->textBox8->TabIndex = 17;
			this->textBox8->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox8_TextChanged);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(285, 112);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(265, 41);
			this->label12->TabIndex = 16;
			this->label12->Text = L"Current Password";
			this->label12->Click += gcnew System::EventHandler(this, &MyForm::label12_Click);
			// 
			// tb_newPassword
			// 
			this->tb_newPassword->Font = (gcnew System::Drawing::Font(L"Segoe UI", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->tb_newPassword->Location = System::Drawing::Point(589, 177);
			this->tb_newPassword->Margin = System::Windows::Forms::Padding(4);
			this->tb_newPassword->Name = L"tb_newPassword";
			this->tb_newPassword->PasswordChar = '*';
			this->tb_newPassword->Size = System::Drawing::Size(333, 42);
			this->tb_newPassword->TabIndex = 15;
			this->tb_newPassword->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox9_TextChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(311, 181);
			this->label13->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(222, 41);
			this->label13->TabIndex = 14;
			this->label13->Text = L"New Password";
			this->label13->Click += gcnew System::EventHandler(this, &MyForm::label13_Click);
			// 
			// pn_editInfo
			// 
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
			this->pn_editInfo->Location = System::Drawing::Point(0, 148);
			this->pn_editInfo->Margin = System::Windows::Forms::Padding(4);
			this->pn_editInfo->Name = L"pn_editInfo";
			this->pn_editInfo->Size = System::Drawing::Size(1204, 597);
			this->pn_editInfo->TabIndex = 2;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Underline)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(405, 37);
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
			this->btn_cancelEdit->Location = System::Drawing::Point(616, 384);
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
			this->btn_saveEdit->Location = System::Drawing::Point(452, 384);
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
			this->tb_edit_phonenumber->Location = System::Drawing::Point(581, 202);
			this->tb_edit_phonenumber->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_phonenumber->Name = L"tb_edit_phonenumber";
			this->tb_edit_phonenumber->Size = System::Drawing::Size(333, 42);
			this->tb_edit_phonenumber->TabIndex = 11;
			this->tb_edit_phonenumber->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_edit_phonenumber_TextChanged);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(287, 198);
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
			this->tb_edit_location->Location = System::Drawing::Point(581, 272);
			this->tb_edit_location->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_location->Name = L"tb_edit_location";
			this->tb_edit_location->Size = System::Drawing::Size(333, 42);
			this->tb_edit_location->TabIndex = 9;
			this->tb_edit_location->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_edit_location_TextChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(287, 270);
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
			this->tb_edit_username->Location = System::Drawing::Point(581, 138);
			this->tb_edit_username->Margin = System::Windows::Forms::Padding(4);
			this->tb_edit_username->Name = L"tb_edit_username";
			this->tb_edit_username->Size = System::Drawing::Size(333, 42);
			this->tb_edit_username->TabIndex = 7;
			this->tb_edit_username->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_edit_username_TextChanged);
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(287, 132);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(164, 41);
			this->label11->TabIndex = 6;
			this->label11->Text = L"UserName";
			// 
			// label1
			// 
			this->label1->Dock = System::Windows::Forms::DockStyle::Top;
			this->label1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(0, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(1204, 148);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Edit Your Information";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
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
			this->pn_blank->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_blank_Paint);
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
			this->pb_blankpicutre->Click += gcnew System::EventHandler(this, &MyForm::pb_blankpicutre_Click);
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
			this->pn_left_bar->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_left_bar_Paint);
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
			this->flowLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::flowLayoutPanel1_Paint);
			// 
			// btn_edit_information
			// 
			this->btn_edit_information->FlatAppearance->BorderSize = 0;
			this->btn_edit_information->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_edit_information->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_edit_information->ForeColor = System::Drawing::Color::White;
			this->btn_edit_information->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_edit_information.Image")));
			this->btn_edit_information->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_edit_information->Location = System::Drawing::Point(3, 20);
			this->btn_edit_information->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_edit_information->Name = L"btn_edit_information";
			this->btn_edit_information->Size = System::Drawing::Size(293, 62);
			this->btn_edit_information->TabIndex = 0;
			this->btn_edit_information->Text = L"Edit Intormation";
			this->btn_edit_information->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_edit_information->UseVisualStyleBackColor = true;
			this->btn_edit_information->Click += gcnew System::EventHandler(this, &MyForm::btn_edit_information_Click);
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
			this->btn_products->Location = System::Drawing::Point(3, 104);
			this->btn_products->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_products->Name = L"btn_products";
			this->btn_products->Size = System::Drawing::Size(293, 66);
			this->btn_products->TabIndex = 1;
			this->btn_products->Text = L"Products";
			this->btn_products->UseVisualStyleBackColor = true;
			this->btn_products->Click += gcnew System::EventHandler(this, &MyForm::btn_products_Click);
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
			this->btn_orders->Location = System::Drawing::Point(3, 192);
			this->btn_orders->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_orders->Name = L"btn_orders";
			this->btn_orders->Size = System::Drawing::Size(293, 65);
			this->btn_orders->TabIndex = 2;
			this->btn_orders->Text = L"Orders";
			this->btn_orders->UseVisualStyleBackColor = true;
			this->btn_orders->Click += gcnew System::EventHandler(this, &MyForm::btn_orders_Click);
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
			this->btn_TotalBill->Location = System::Drawing::Point(3, 279);
			this->btn_TotalBill->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_TotalBill->Name = L"btn_TotalBill";
			this->btn_TotalBill->Size = System::Drawing::Size(293, 64);
			this->btn_TotalBill->TabIndex = 4;
			this->btn_TotalBill->Text = L"Total Bill";
			this->btn_TotalBill->UseVisualStyleBackColor = true;
			this->btn_TotalBill->Click += gcnew System::EventHandler(this, &MyForm::btn_TotalBill_Click);
			// 
			// btn_login
			// 
			this->btn_login->FlatAppearance->BorderSize = 0;
			this->btn_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btn_login->ForeColor = System::Drawing::Color::White;
			this->btn_login->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_login.Image")));
			this->btn_login->ImageAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_login->Location = System::Drawing::Point(3, 430);
			this->btn_login->Margin = System::Windows::Forms::Padding(3, 85, 3, 2);
			this->btn_login->Name = L"btn_login";
			this->btn_login->Size = System::Drawing::Size(293, 98);
			this->btn_login->TabIndex = 3;
			this->btn_login->Text = L"Log out";
			this->btn_login->UseVisualStyleBackColor = true;
			this->btn_login->Click += gcnew System::EventHandler(this, &MyForm::btn_login_Click);
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
			this->pn_picture->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_picture_Paint);
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
			this->lb_profile->Click += gcnew System::EventHandler(this, &MyForm::lb_profile_Click);
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
			this->pb_profile->Click += gcnew System::EventHandler(this, &MyForm::pb_profile_Click);
			// 
			// pn_login
			// 
			this->pn_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_login.BackgroundImage")));
			this->pn_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
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
			this->pn_login->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_login_Paint);
			// 
			// pictureBox2
			// 
			this->pictureBox2->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox2->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.BackgroundImage")));
			this->pictureBox2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox2->Location = System::Drawing::Point(509, 54);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(87, 62);
			this->pictureBox2->TabIndex = 23;
			this->pictureBox2->TabStop = false;
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::White;
			this->label3->Location = System::Drawing::Point(605, 48);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(213, 68);
			this->label3->TabIndex = 22;
			this->label3->Text = L"Login";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// lb_password_message_login
			// 
			this->lb_password_message_login->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_message_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_message_login->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_password_message_login->Location = System::Drawing::Point(563, 358);
			this->lb_password_message_login->Name = L"lb_password_message_login";
			this->lb_password_message_login->Size = System::Drawing::Size(325, 23);
			this->lb_password_message_login->TabIndex = 21;
			this->lb_password_message_login->Text = L"Please enter the password";
			this->lb_password_message_login->Click += gcnew System::EventHandler(this, &MyForm::lb_password_message_login_Click);
			// 
			// lb_username_message_login
			// 
			this->lb_username_message_login->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_message_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_message_login->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_username_message_login->Location = System::Drawing::Point(564, 244);
			this->lb_username_message_login->Name = L"lb_username_message_login";
			this->lb_username_message_login->Size = System::Drawing::Size(325, 23);
			this->lb_username_message_login->TabIndex = 20;
			this->lb_username_message_login->Text = L" Please enter the username";
			this->lb_username_message_login->Click += gcnew System::EventHandler(this, &MyForm::lb_username_message_login_Click);
			// 
			// btn_refresh_password_login
			// 
			this->btn_refresh_password_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_password_login.BackgroundImage")));
			this->btn_refresh_password_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_password_login->FlatAppearance->BorderSize = 0;
			this->btn_refresh_password_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_password_login->Location = System::Drawing::Point(899, 331);
			this->btn_refresh_password_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_password_login->Name = L"btn_refresh_password_login";
			this->btn_refresh_password_login->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_password_login->TabIndex = 19;
			this->btn_refresh_password_login->UseVisualStyleBackColor = true;
			this->btn_refresh_password_login->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_password_login_Click);
			// 
			// btn_refresh_username_login
			// 
			this->btn_refresh_username_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_username_login.BackgroundImage")));
			this->btn_refresh_username_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_username_login->FlatAppearance->BorderSize = 0;
			this->btn_refresh_username_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_username_login->Location = System::Drawing::Point(899, 217);
			this->btn_refresh_username_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_username_login->Name = L"btn_refresh_username_login";
			this->btn_refresh_username_login->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_username_login->TabIndex = 18;
			this->btn_refresh_username_login->UseVisualStyleBackColor = true;
			this->btn_refresh_username_login->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_username_login_Click);
			// 
			// btn_seepasword_login
			// 
			this->btn_seepasword_login->BackColor = System::Drawing::Color::White;
			this->btn_seepasword_login->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepasword_login.BackgroundImage")));
			this->btn_seepasword_login->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepasword_login->FlatAppearance->BorderSize = 0;
			this->btn_seepasword_login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepasword_login->Location = System::Drawing::Point(832, 332);
			this->btn_seepasword_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_seepasword_login->Name = L"btn_seepasword_login";
			this->btn_seepasword_login->Size = System::Drawing::Size(61, 22);
			this->btn_seepasword_login->TabIndex = 15;
			this->btn_seepasword_login->UseVisualStyleBackColor = false;
			this->btn_seepasword_login->Click += gcnew System::EventHandler(this, &MyForm::btn_seepasword_login_Click);
			// 
			// tb_password_login
			// 
			this->tb_password_login->Location = System::Drawing::Point(563, 332);
			this->tb_password_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_password_login->Name = L"tb_password_login";
			this->tb_password_login->Size = System::Drawing::Size(329, 22);
			this->tb_password_login->TabIndex = 1;
			this->tb_password_login->UseSystemPasswordChar = true;
			this->tb_password_login->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_password_login_TextChanged);
			// 
			// tb_username_login
			// 
			this->tb_username_login->Location = System::Drawing::Point(563, 218);
			this->tb_username_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_username_login->Name = L"tb_username_login";
			this->tb_username_login->Size = System::Drawing::Size(329, 22);
			this->tb_username_login->TabIndex = 0;
			this->tb_username_login->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_username_login_TextChanged);
			// 
			// lb_password
			// 
			this->lb_password->BackColor = System::Drawing::Color::Transparent;
			this->lb_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_password->ForeColor = System::Drawing::Color::White;
			this->lb_password->Location = System::Drawing::Point(381, 329);
			this->lb_password->Name = L"lb_password";
			this->lb_password->Size = System::Drawing::Size(155, 34);
			this->lb_password->TabIndex = 4;
			this->lb_password->Text = L"Password";
			this->lb_password->Click += gcnew System::EventHandler(this, &MyForm::lb_password_Click);
			// 
			// lb_username
			// 
			this->lb_username->BackColor = System::Drawing::Color::Transparent;
			this->lb_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_username->ForeColor = System::Drawing::Color::White;
			this->lb_username->Location = System::Drawing::Point(381, 215);
			this->lb_username->Name = L"lb_username";
			this->lb_username->Size = System::Drawing::Size(155, 34);
			this->lb_username->TabIndex = 3;
			this->lb_username->Text = L"Username";
			this->lb_username->Click += gcnew System::EventHandler(this, &MyForm::lb_username_Click);
			// 
			// btn_register_loginpanel
			// 
			this->btn_register_loginpanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_register_loginpanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_register_loginpanel->FlatAppearance->BorderSize = 0;
			this->btn_register_loginpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_register_loginpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_register_loginpanel->ForeColor = System::Drawing::Color::White;
			this->btn_register_loginpanel->Location = System::Drawing::Point(368, 569);
			this->btn_register_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_register_loginpanel->Name = L"btn_register_loginpanel";
			this->btn_register_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_register_loginpanel->TabIndex = 3;
			this->btn_register_loginpanel->Text = L"Register";
			this->btn_register_loginpanel->UseVisualStyleBackColor = false;
			this->btn_register_loginpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_register_loginpanel_Click);
			// 
			// btn_back_loginpanal
			// 
			this->btn_back_loginpanal->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_back_loginpanal->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_back_loginpanal->FlatAppearance->BorderSize = 0;
			this->btn_back_loginpanal->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_back_loginpanal->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_back_loginpanal->ForeColor = System::Drawing::Color::White;
			this->btn_back_loginpanal->Location = System::Drawing::Point(709, 569);
			this->btn_back_loginpanal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_back_loginpanal->Name = L"btn_back_loginpanal";
			this->btn_back_loginpanal->Size = System::Drawing::Size(229, 58);
			this->btn_back_loginpanal->TabIndex = 4;
			this->btn_back_loginpanal->Text = L"Back";
			this->btn_back_loginpanal->UseVisualStyleBackColor = false;
			this->btn_back_loginpanal->Click += gcnew System::EventHandler(this, &MyForm::btn_back_loginpanal_Click);
			// 
			// btn_login_loginpanel
			// 
			this->btn_login_loginpanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)), static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->btn_login_loginpanel->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->btn_login_loginpanel->FlatAppearance->BorderSize = 0;
			this->btn_login_loginpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_login_loginpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_login_loginpanel->ForeColor = System::Drawing::Color::White;
			this->btn_login_loginpanel->Location = System::Drawing::Point(529, 462);
			this->btn_login_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_login_loginpanel->Name = L"btn_login_loginpanel";
			this->btn_login_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_login_loginpanel->TabIndex = 2;
			this->btn_login_loginpanel->Text = L"Log in";
			this->btn_login_loginpanel->UseVisualStyleBackColor = false;
			this->btn_login_loginpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_login_loginpanel_Click);
			// 
			// pn_register
			// 
			this->pn_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pn_register.BackgroundImage")));
			this->pn_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pn_register->Controls->Add(this->pictureBox1);
			this->pn_register->Controls->Add(this->label4);
			this->pn_register->Controls->Add(this->btn_refresh_location_register);
			this->pn_register->Controls->Add(this->btn_refresh_phonenumber_register);
			this->pn_register->Controls->Add(this->btn_refresh_password_register);
			this->pn_register->Controls->Add(this->btn_refresh_username_register);
			this->pn_register->Controls->Add(this->btn_seepassword);
			this->pn_register->Controls->Add(this->link_login);
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
			this->pn_register->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_register_Paint);
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pictureBox1->Location = System::Drawing::Point(511, 28);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(87, 62);
			this->pictureBox1->TabIndex = 21;
			this->pictureBox1->TabStop = false;
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI", 26.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::White;
			this->label4->Location = System::Drawing::Point(604, 22);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(213, 68);
			this->label4->TabIndex = 20;
			this->label4->Text = L"Register";
			this->label4->Click += gcnew System::EventHandler(this, &MyForm::label4_Click);
			// 
			// btn_refresh_location_register
			// 
			this->btn_refresh_location_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_location_register.BackgroundImage")));
			this->btn_refresh_location_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_location_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_location_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_location_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_location_register->Location = System::Drawing::Point(980, 402);
			this->btn_refresh_location_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_location_register->Name = L"btn_refresh_location_register";
			this->btn_refresh_location_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_location_register->TabIndex = 18;
			this->btn_refresh_location_register->UseVisualStyleBackColor = true;
			this->btn_refresh_location_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_location_register_Click);
			// 
			// btn_refresh_phonenumber_register
			// 
			this->btn_refresh_phonenumber_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_phonenumber_register.BackgroundImage")));
			this->btn_refresh_phonenumber_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_phonenumber_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_phonenumber_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_phonenumber_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_phonenumber_register->Location = System::Drawing::Point(980, 305);
			this->btn_refresh_phonenumber_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_phonenumber_register->Name = L"btn_refresh_phonenumber_register";
			this->btn_refresh_phonenumber_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_phonenumber_register->TabIndex = 17;
			this->btn_refresh_phonenumber_register->UseVisualStyleBackColor = true;
			this->btn_refresh_phonenumber_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_phonenumber_register_Click);
			// 
			// btn_refresh_password_register
			// 
			this->btn_refresh_password_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_password_register.BackgroundImage")));
			this->btn_refresh_password_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_password_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_password_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_password_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_password_register->Location = System::Drawing::Point(980, 219);
			this->btn_refresh_password_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_password_register->Name = L"btn_refresh_password_register";
			this->btn_refresh_password_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_password_register->TabIndex = 16;
			this->btn_refresh_password_register->UseVisualStyleBackColor = true;
			this->btn_refresh_password_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_password_register_Click);
			// 
			// btn_refresh_username_register
			// 
			this->btn_refresh_username_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_username_register.BackgroundImage")));
			this->btn_refresh_username_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_username_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_username_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_username_register->ForeColor = System::Drawing::Color::Transparent;
			this->btn_refresh_username_register->Location = System::Drawing::Point(980, 128);
			this->btn_refresh_username_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_refresh_username_register->Name = L"btn_refresh_username_register";
			this->btn_refresh_username_register->Size = System::Drawing::Size(39, 23);
			this->btn_refresh_username_register->TabIndex = 15;
			this->btn_refresh_username_register->UseVisualStyleBackColor = true;
			this->btn_refresh_username_register->Click += gcnew System::EventHandler(this, &MyForm::btn_refresh_username_register_Click);
			// 
			// btn_seepassword
			// 
			this->btn_seepassword->BackColor = System::Drawing::Color::White;
			this->btn_seepassword->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_seepassword.BackgroundImage")));
			this->btn_seepassword->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_seepassword->FlatAppearance->BorderSize = 0;
			this->btn_seepassword->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_seepassword->Location = System::Drawing::Point(913, 220);
			this->btn_seepassword->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_seepassword->Name = L"btn_seepassword";
			this->btn_seepassword->Size = System::Drawing::Size(61, 22);
			this->btn_seepassword->TabIndex = 14;
			this->btn_seepassword->UseVisualStyleBackColor = false;
			this->btn_seepassword->Click += gcnew System::EventHandler(this, &MyForm::btn_seepassword_Click);
			// 
			// link_login
			// 
			this->link_login->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->link_login->LinkColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->link_login->Location = System::Drawing::Point(647, 591);
			this->link_login->Name = L"link_login";
			this->link_login->Size = System::Drawing::Size(81, 36);
			this->link_login->TabIndex = 13;
			this->link_login->TabStop = true;
			this->link_login->Text = L"login";
			this->link_login->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linklogin_LinkClicked);
			// 
			// lb_location_message
			// 
			this->lb_location_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_location_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_location_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_location_message->Location = System::Drawing::Point(649, 428);
			this->lb_location_message->Name = L"lb_location_message";
			this->lb_location_message->Size = System::Drawing::Size(325, 23);
			this->lb_location_message->TabIndex = 12;
			this->lb_location_message->Text = L"Enter the location";
			this->lb_location_message->Click += gcnew System::EventHandler(this, &MyForm::lb_location_message_Click);
			// 
			// lb_phonenumber_message
			// 
			this->lb_phonenumber_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_phonenumber_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_phonenumber_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_phonenumber_message->Location = System::Drawing::Point(656, 334);
			this->lb_phonenumber_message->Name = L"lb_phonenumber_message";
			this->lb_phonenumber_message->Size = System::Drawing::Size(325, 23);
			this->lb_phonenumber_message->TabIndex = 11;
			this->lb_phonenumber_message->Text = L"Enter the phone number";
			this->lb_phonenumber_message->Click += gcnew System::EventHandler(this, &MyForm::lb_phonenumber_message_Click);
			// 
			// lb_password_message
			// 
			this->lb_password_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_password_message->Location = System::Drawing::Point(649, 245);
			this->lb_password_message->Name = L"lb_password_message";
			this->lb_password_message->Size = System::Drawing::Size(325, 23);
			this->lb_password_message->TabIndex = 10;
			this->lb_password_message->Text = L"Enter the password";
			this->lb_password_message->Click += gcnew System::EventHandler(this, &MyForm::lb_password_message_Click);
			// 
			// lb_username_message
			// 
			this->lb_username_message->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_username_message->Location = System::Drawing::Point(649, 154);
			this->lb_username_message->Name = L"lb_username_message";
			this->lb_username_message->Size = System::Drawing::Size(325, 23);
			this->lb_username_message->TabIndex = 9;
			this->lb_username_message->Text = L"Enter the username";
			this->lb_username_message->Click += gcnew System::EventHandler(this, &MyForm::lb_username_message_Click);
			// 
			// btn_register_registerpanel
			// 
			this->btn_register_registerpanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_register_registerpanel->FlatAppearance->BorderSize = 0;
			this->btn_register_registerpanel->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_register_registerpanel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_register_registerpanel->Location = System::Drawing::Point(573, 508);
			this->btn_register_registerpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_register_registerpanel->Name = L"btn_register_registerpanel";
			this->btn_register_registerpanel->Size = System::Drawing::Size(244, 64);
			this->btn_register_registerpanel->TabIndex = 8;
			this->btn_register_registerpanel->Text = L"Register";
			this->btn_register_registerpanel->UseVisualStyleBackColor = false;
			this->btn_register_registerpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_register_registerpanel_Click);
			// 
			// tb_location_register
			// 
			this->tb_location_register->Location = System::Drawing::Point(649, 404);
			this->tb_location_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_location_register->Name = L"tb_location_register";
			this->tb_location_register->Size = System::Drawing::Size(325, 22);
			this->tb_location_register->TabIndex = 7;
			this->tb_location_register->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_location_register_TextChanged);
			// 
			// tb_phonenumber_register
			// 
			this->tb_phonenumber_register->Location = System::Drawing::Point(649, 306);
			this->tb_phonenumber_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_phonenumber_register->Name = L"tb_phonenumber_register";
			this->tb_phonenumber_register->Size = System::Drawing::Size(325, 22);
			this->tb_phonenumber_register->TabIndex = 6;
			this->tb_phonenumber_register->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_phonenumber_register_TextChanged);
			// 
			// tb_password_register
			// 
			this->tb_password_register->Location = System::Drawing::Point(649, 220);
			this->tb_password_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_password_register->Name = L"tb_password_register";
			this->tb_password_register->Size = System::Drawing::Size(325, 22);
			this->tb_password_register->TabIndex = 5;
			this->tb_password_register->UseSystemPasswordChar = true;
			this->tb_password_register->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_password_register_TextChanged);
			// 
			// tb_username_register
			// 
			this->tb_username_register->Location = System::Drawing::Point(649, 129);
			this->tb_username_register->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->tb_username_register->Name = L"tb_username_register";
			this->tb_username_register->Size = System::Drawing::Size(325, 22);
			this->tb_username_register->TabIndex = 4;
			this->tb_username_register->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_username_username_TextChanged);
			// 
			// lb_password_register
			// 
			this->lb_password_register->AutoSize = true;
			this->lb_password_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_password_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_register->ForeColor = System::Drawing::Color::White;
			this->lb_password_register->Location = System::Drawing::Point(395, 210);
			this->lb_password_register->Name = L"lb_password_register";
			this->lb_password_register->Size = System::Drawing::Size(153, 32);
			this->lb_password_register->TabIndex = 3;
			this->lb_password_register->Text = L"Password :";
			this->lb_password_register->Click += gcnew System::EventHandler(this, &MyForm::lb_password_register_Click);
			// 
			// lb_phonenumber_register
			// 
			this->lb_phonenumber_register->AutoSize = true;
			this->lb_phonenumber_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_phonenumber_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_phonenumber_register->ForeColor = System::Drawing::Color::White;
			this->lb_phonenumber_register->Location = System::Drawing::Point(395, 299);
			this->lb_phonenumber_register->Name = L"lb_phonenumber_register";
			this->lb_phonenumber_register->Size = System::Drawing::Size(215, 32);
			this->lb_phonenumber_register->TabIndex = 2;
			this->lb_phonenumber_register->Text = L"Phone number :";
			this->lb_phonenumber_register->Click += gcnew System::EventHandler(this, &MyForm::lb_phonenumber_register_Click);
			// 
			// lb_location
			// 
			this->lb_location->AutoSize = true;
			this->lb_location->BackColor = System::Drawing::Color::Transparent;
			this->lb_location->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_location->ForeColor = System::Drawing::Color::White;
			this->lb_location->Location = System::Drawing::Point(395, 394);
			this->lb_location->Name = L"lb_location";
			this->lb_location->Size = System::Drawing::Size(138, 32);
			this->lb_location->TabIndex = 1;
			this->lb_location->Text = L"Location :";
			this->lb_location->Click += gcnew System::EventHandler(this, &MyForm::lb_location_Click);
			// 
			// lb_username_register
			// 
			this->lb_username_register->AutoSize = true;
			this->lb_username_register->BackColor = System::Drawing::Color::Transparent;
			this->lb_username_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_register->ForeColor = System::Drawing::Color::White;
			this->lb_username_register->Location = System::Drawing::Point(395, 119);
			this->lb_username_register->Name = L"lb_username_register";
			this->lb_username_register->Size = System::Drawing::Size(159, 32);
			this->lb_username_register->TabIndex = 0;
			this->lb_username_register->Text = L"Username :";
			this->lb_username_register->Click += gcnew System::EventHandler(this, &MyForm::lb_username_register_Click);
			// 
			// pn_thankyou
			// 
			this->pn_thankyou->Controls->Add(this->thankyou);
			this->pn_thankyou->Location = System::Drawing::Point(0, 0);
			this->pn_thankyou->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_thankyou->Name = L"pn_thankyou";
			this->pn_thankyou->Size = System::Drawing::Size(1500, 745);
			this->pn_thankyou->TabIndex = 0;
			this->pn_thankyou->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::pn_thankyou_Paint);
			// 
			// thankyou
			// 
			this->thankyou->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->thankyou->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->thankyou->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"thankyou.Image")));
			this->thankyou->Location = System::Drawing::Point(0, 0);
			this->thankyou->Margin = System::Windows::Forms::Padding(4);
			this->thankyou->Name = L"thankyou";
			this->thankyou->Size = System::Drawing::Size(1500, 745);
			this->thankyou->TabIndex = 0;
			this->thankyou->TabStop = false;
			this->thankyou->Click += gcnew System::EventHandler(this, &MyForm::thankyou_Click);
			// 
			// timerforexit
			// 
			this->timerforexit->Interval = 3000;
			this->timerforexit->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
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
			this->pn_start->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->EndInit();
			this->pn_defualt->ResumeLayout(false);
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
			this->pn_edit_information->ResumeLayout(false);
			this->pn_currentInfo->ResumeLayout(false);
			this->pn_currentInfo->PerformLayout();
			this->pn_resetPassword->ResumeLayout(false);
			this->pn_resetPassword->PerformLayout();
			this->pn_editInfo->ResumeLayout(false);
			this->pn_editInfo->PerformLayout();
			this->pn_blank->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->EndInit();
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_picture->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->EndInit();
			this->pn_login->ResumeLayout(false);
			this->pn_login->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->pn_register->ResumeLayout(false);
			this->pn_register->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->pn_thankyou->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thankyou))->EndInit();
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

	private: System::Void btn_close_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		this->WindowState = FormWindowState::Minimized;
	}
	private: System::Void btn_edit_information_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_edit_information);
		showCategoryPanel(pn_currentInfo);
		populateCurrentUserInfo(sender, e);
	}
	private: System::Void btn_products_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_products);
		pn_main_category->BringToFront();
	}

	private: System::Void btn_orders_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_orders);
		loadCurrentUserOrder();
	}
	private: System::Void btn_login_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_login);
	}
	private: System::Void btn_exit_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->ForeColor = Color::FromArgb(0xE6, 0x34, 0x62);
	}
	private: System::Void btn_exit_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->ForeColor = Color::Black;

	}
	private: System::Void btn_exit_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_thankyou);
		timerforexit->Interval = 15000; // 15 seconds
		timerforexit->Start();
	}
	private: System::Void button1_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_exit->ForeColor = Color::FromArgb(0xE6, 0x34, 0x62);
	}
	private: System::Void btn_start_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
		btn_start->ForeColor = Color::FromArgb(0xDA, 0xF5, 0xF2);
	}
	private: System::Void btn_start_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
		btn_start->ForeColor = Color::Black;
	}
	private: System::Void btn_start_MouseHover(System::Object^ sender, System::EventArgs^ e) {
		btn_start->ForeColor = Color::Wheat;
	}
	private: System::Void btn_start_Click(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_login);

	}
	private: System::Void btn_login_loginpanel_Click(System::Object^ sender, System::EventArgs^ e) {
		if (tb_username_login->Text->Trim() != "" && tb_password_login->Text->Trim() != "") {
			StreamReader^ sr = gcnew StreamReader("customers.txt");
			String^ line = "";
			int index = 0;
			bool found = false;

			while ((line = sr->ReadLine()) != nullptr) {
				array<String^>^ parts = line->Split(',');
				if (parts->Length < 5) continue;

				String^ fileID = parts[0]->Trim();
				String^ fileUser = parts[1]->Trim();
				String^ filePhone = parts[2]->Trim();
				String^ fileLocation = parts[3]->Trim();
				String^ filePass = parts[4]->Trim();

				if (tb_username_login->Text->Trim() == fileUser && tb_password_login->Text->Trim() == filePass) {
					CUSTOMER^ c = gcnew CUSTOMER();
					c->ID = Convert::ToInt32(fileID);
					c->Name = fileUser;
					c->Password = filePass;
					c->PhoneNumber = filePhone;
					c->Location = fileLocation;
					customers[index] = c;

					currentCustomerIndex = index;
					lb_profile->Text = fileUser->ToUpper();

					showPanel(pn_defualt);
					showPanel(pn_blank);
					tb_username_login->Text = "";
					tb_password_login->Text = "";
					found = true;
					break;
				}
				index++;
			}
			sr->Close();

			if (!found) {
				lb_username_message_login->Text = "Username is incorrect.";
				lb_password_message_login->Text = "Password is incorrect.";
			}
		}
		else {
			MessageBox::Show("Login failed. Please check your username and password.");
			tb_username_login->Focus();
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
	private: System::Void lb_profile_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void welcomeScreen_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_minimize_MouseHover(System::Object^ sender, System::EventArgs^ e) {
	}

private: System::Void btn_register_registerpanel_Click(System::Object^ sender, System::EventArgs^ e) {
	bool hasError = false;

	// Extract input values
	String^ username = tb_username_register->Text->Trim();
	String^ password = tb_password_register->Text->Trim();
	String^ phone = tb_phonenumber_register->Text->Trim();
	String^ location = tb_location_register->Text->Trim();

	// === Password Validation ===
	if (password->Length != 8 || !System::Text::RegularExpressions::Regex::IsMatch(password, "^[0-9]{8}$")) {
		lb_password_message->Text = "Password must be exactly 8 digits.";
		tb_password_register->Focus();
		tb_password_register->SelectAll();
		hasError = true;
	}
	else {
		lb_password_message->Text = "";
	}

	// === Phone Number Validation ===
	if (phone->Length != 11 || !System::Text::RegularExpressions::Regex::IsMatch(phone, "^[0-9]{11}$")) {
		lb_phonenumber_message->Text = "Phone number must be exactly 11 digits.";
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

	if (username == "") {
		lb_username_message->Text = "Username is required.";
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
	if (location == "") {
		lb_location_message->Text = "Location is required.";
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




	private: System::Void tb_username_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
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
	


	private: System::Void pn_register_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_upper_bar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void lb_brand_name_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pb_icon_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_main_dashboard_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void lb_password_message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_location_message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_phonenumber_message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_username_message_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_location_register_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_phonenumber_register_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_password_register_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_password_register_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_phonenumber_register_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_location_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_username_register_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_start_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void welcomeScreen_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_defualt_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_blank_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pb_blankpicutre_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_products_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_main_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void flowLayoutPanel2_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void btn_fruits_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_fruits_category);
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
	private: System::Void btn_snacks_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_snacks_category);

	}
	private: System::Void btn_household_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_household_category);

	}
	private: System::Void btn_pet_Click(System::Object^ sender, System::EventArgs^ e) {
		showCategoryPanel(pn_pet_supplies_category);

	}
	private: System::Void pn_fruits_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_vegetable_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_bakery_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_household_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_snacks_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_poultry_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_butchershop_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_seafood_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_pet_supplies_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_dairy_category_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_edit_information_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_orders_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void label2_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_left_bar_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void flowLayoutPanel1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pn_picture_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void pb_profile_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_login_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void lb_password_message_login_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_username_message_login_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_password_login_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_username_login_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_password_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lb_username_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void pn_thankyou_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	}
	private: System::Void thankyou_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void timer1_Tick_1(System::Object^ sender, System::EventArgs^ e) {
		this->Close();

	}
	private: System::Void label4_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	

	private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_edit_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {

	}
	private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void tb_location_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}

	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_editInfo_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_editInfo->BringToFront();
	}
	private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {
		pn_resetPassword->BringToFront();
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
			if (newPhone == "" || newPhone->Length != 11 || !System::Text::RegularExpressions::Regex::IsMatch(newPhone, "^[0-9]{11}$")) {
				MessageBox::Show("Phone number must be exactly 11 digits.");
				tb_edit_phonenumber->Focus();
				tb_edit_phonenumber->SelectAll();
				hasError = true;
			}

			// === Name Validation ===
			if (newName == "") {
				MessageBox::Show("Name cannot be empty.");
				tb_edit_username->Focus();
				hasError = true;
			}
			else {
				// Check if name already exists (excluding current user)
				array<String^>^ lines = File::ReadAllLines("customers.txt");
				for each (String ^ line in lines) {
					array<String^>^ parts = line->Split(',');
					if (parts->Length < 5) continue;

					if (parts[1]->Trim()->ToLower() == newName->ToLower() && parts[0]->Trim() != currentID) {
						MessageBox::Show("This name is already taken by another user.");
						tb_edit_username->Focus();
						hasError = true;
						break;
					}
				}
			}

			// === Location Validation ===
			if (newLocation == "") {
				MessageBox::Show("Location cannot be empty.");
				tb_edit_location->Focus();
				hasError = true;
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
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		//save new password
		String^ newPassword = tb_newPassword->Text->Trim();

		String^ confirmPassword = tb_confirmPassword->Text->Trim();
		if (newPassword != confirmPassword) {
			MessageBox::Show("Passwords do not match.");
			return;
		}
		if (newPassword->Length != 8 || !System::Text::RegularExpressions::Regex::IsMatch(newPassword, "^[0-9]{8}$")) {
			MessageBox::Show("Password must be exactly 8 digits.");
			return;
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
	private: System::Void textBox8_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_currentInfo->BringToFront();
	}
	private: System::Void textBox9_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label13_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label12_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void btn_reset_Click(System::Object^ sender, System::EventArgs^ e) {
		pn_resetPassword->BringToFront();
	}
	
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		showPanel(pn_start);
	}
private: System::Void tb_edit_username_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tb_edit_phonenumber_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tb_edit_location_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void label17_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void tb_confirmPassword_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_TotalBill_Click(System::Object^ sender, System::EventArgs^ e) {
	showPanel(pn_viewBill);
}
	   private: System::Void saveCurrentOrderToFile() {
		   if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr) return;

		   try {
			   ORDER^ order = orders[currentCustomerIndex];
			   if (order == nullptr || order->productcount == 0) {
				   // If no products left, clear the file
				   File::WriteAllText("order.txt", "");
				   return;
			   }

			   String^ line = order->CustomerID.ToString() + "|";

			   for (int i = 0; i < order->productcount; i++) {
				   String^ productName = order->Products[i]->Name;
				   double qty = order->Amount[i];
				   double unitPrice = order->Products[i]->Price;

				   line += productName + "," + qty.ToString("F2") + "," + unitPrice.ToString("F2");

				   if (i < order->productcount - 1)
					   line += ";"; // add separator if not last
			   }

			   line += "|" + order->TotalPrice.ToString("F2");

			   // Save only the current user's order
			   array<String^>^ newLine = { line };
			   File::WriteAllLines("order.txt", newLine); // overwrite the file
		   }
		   catch (Exception^ ex) {
			   MessageBox::Show("Error saving order: " + ex->Message);
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

private: System::Void loadCurrentUserOrder() {
	if (currentCustomerIndex < 0 || customers[currentCustomerIndex] == nullptr) return;

	try {
		pn_orders->Controls->Clear();

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

				// === Rebuild the ORDER struct properly ===
				orders[currentCustomerIndex] = gcnew ORDER();
				orders[currentCustomerIndex]->CustomerID = fileCustomerID;
				orders[currentCustomerIndex]->TotalPrice = totalPrice;
				orders[currentCustomerIndex]->productcount = 0;

				FlowLayoutPanel^ orderList = gcnew FlowLayoutPanel();
				orderList->Dock = DockStyle::Fill;
				orderList->AutoScroll = true;
				pn_orders->Controls->Add(orderList);

				array<String^>^ productEntries = productsPart->Split(';');

				for each (String ^ productEntry in productEntries) {
					if (String::IsNullOrWhiteSpace(productEntry)) continue;

					array<String^>^ prodParts = productEntry->Split(',');

					String^ productName = prodParts[0]->Trim();
					double qty = Convert::ToDouble(prodParts[1]);
					double unitPrice = Convert::ToDouble(prodParts[2]);

					// === Add into orders[currentCustomerIndex] memory ===
					PRODUCT^ product = gcnew PRODUCT();
					product->Name = productName;
					product->Price = unitPrice;

					int idx = orders[currentCustomerIndex]->productcount;
					orders[currentCustomerIndex]->Products[idx] = product;
					orders[currentCustomerIndex]->Amount[idx] = qty;
					orders[currentCustomerIndex]->productcount++;

					// === Create UI ===
					Panel^ itemPanel = gcnew Panel();
					itemPanel->Height = 120;
					itemPanel->Width = 800;
					itemPanel->BackColor = Color::White;
					itemPanel->Margin = System::Windows::Forms::Padding(10);

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
					lblInfo->Text = "Product: " + productName + "\nQuantity: " + qty.ToString("F2") + "\nUnit Price: " + unitPrice.ToString("F2") + " EGP\nTotal: " + (qty * unitPrice).ToString("F2") + " EGP";
					lblInfo->Location = Point(130, 20);
					lblInfo->Width = 450;
					lblInfo->Height = 80;
					lblInfo->Font = gcnew Drawing::Font("Segoe UI", 12);
					itemPanel->Controls->Add(lblInfo);

					Button^ btnDelete = gcnew Button();
					btnDelete->Text = "Delete";
					btnDelete->Width = 100;
					btnDelete->Height = 30;
					btnDelete->BackColor = Color::FromArgb(220, 20, 60);
					btnDelete->ForeColor = Color::White;
					btnDelete->Location = Point(600, 40);
					btnDelete->Tag = productName;
					btnDelete->Click += gcnew EventHandler(this, &MyForm::deleteButton_Click);
					itemPanel->Controls->Add(btnDelete);

					orderList->Controls->Add(itemPanel);
				}

				// === Total Price Label ===
				Label^ lblTotal = gcnew Label();
				lblTotal->Text = "TOTAL ORDER: " + totalPrice.ToString("F2") + " EGP";
				lblTotal->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
				lblTotal->ForeColor = Color::DarkGreen;
				lblTotal->Width = 800;
				lblTotal->Height = 40;
				lblTotal->TextAlign = ContentAlignment::MiddleCenter;

				orderList->Controls->Add(lblTotal);

				break;
			}
		}

		if (!foundOrder) {
			Label^ lblNoOrder = gcnew Label();
			lblNoOrder->Text = "No orders found.";
			lblNoOrder->Font = gcnew Drawing::Font("Segoe UI", 16, FontStyle::Bold);
			lblNoOrder->ForeColor = Color::Gray;
			lblNoOrder->Dock = DockStyle::Top;
			pn_orders->Controls->Add(lblNoOrder);
		}
	}
	catch (Exception^ ex) {
		MessageBox::Show("Error loading order: " + ex->Message);
	}
}

private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
	timerforexit->Stop();  // Stop the timer
	Application::Exit();   // Now exit nicely
}
};
}
