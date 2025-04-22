#pragma once
#include "MyForm.h"

namespace SuperMarkoGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
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
	private: System::Windows::Forms::Label^ label4;

	private: System::Windows::Forms::Label^ label2;
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





	private: System::Windows::Forms::Panel^ panel5;
	private: System::Windows::Forms::Panel^ panel4;
	private: System::Windows::Forms::Panel^ panel3;
	private: System::Windows::Forms::Panel^ panel2;
	private: System::Windows::Forms::Panel^ pn_fruits;

	private: System::Windows::Forms::Panel^ pn_main_window;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Panel^ panel11;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::Button^ btn_category_fruits;
	private: System::Windows::Forms::Button^ btn_category_vegetable;
	private: System::Windows::Forms::Button^ btn_category_dairy;
	private: System::Windows::Forms::Button^ btn_category_butcher_shop;
	private: System::Windows::Forms::Button^ btn_category_seafood;
	private: System::Windows::Forms::Button^ btn_category_poultry;
	private: System::Windows::Forms::Button^ btn_category_bakery;
	private: System::Windows::Forms::Button^ btn_category_snacks;











	private: System::Windows::Forms::Button^ btn_category_household;
	private: System::Windows::Forms::Button^ btn_category_pet_supplies;



























































	protected:


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->pn_upper_bar = (gcnew System::Windows::Forms::Panel());
			this->lb_brand_name = (gcnew System::Windows::Forms::Label());
			this->pb_icon = (gcnew System::Windows::Forms::PictureBox());
			this->btn_minimize = (gcnew System::Windows::Forms::Button());
			this->btn_close = (gcnew System::Windows::Forms::Button());
			this->pn_main_dashboard = (gcnew System::Windows::Forms::Panel());
			this->pn_defualt = (gcnew System::Windows::Forms::Panel());
			this->pn_products = (gcnew System::Windows::Forms::Panel());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btn_category_fruits = (gcnew System::Windows::Forms::Button());
			this->btn_category_vegetable = (gcnew System::Windows::Forms::Button());
			this->btn_category_dairy = (gcnew System::Windows::Forms::Button());
			this->btn_category_butcher_shop = (gcnew System::Windows::Forms::Button());
			this->btn_category_seafood = (gcnew System::Windows::Forms::Button());
			this->btn_category_poultry = (gcnew System::Windows::Forms::Button());
			this->btn_category_bakery = (gcnew System::Windows::Forms::Button());
			this->btn_category_snacks = (gcnew System::Windows::Forms::Button());
			this->btn_category_household = (gcnew System::Windows::Forms::Button());
			this->btn_category_pet_supplies = (gcnew System::Windows::Forms::Button());
			this->pn_fruits = (gcnew System::Windows::Forms::Panel());
			this->pn_vegetable = (gcnew System::Windows::Forms::Panel());
			this->pn_dairy = (gcnew System::Windows::Forms::Panel());
			this->pn_butcher_shop = (gcnew System::Windows::Forms::Panel());
			this->pn_seafood = (gcnew System::Windows::Forms::Panel());
			this->pn_ = (gcnew System::Windows::Forms::Panel());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->pn_main_window = (gcnew System::Windows::Forms::Panel());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pn_edit_information = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pn_blank = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pn_orders = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pn_left_bar = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btn_edit_information = (gcnew System::Windows::Forms::Button());
			this->btn_products = (gcnew System::Windows::Forms::Button());
			this->btn_orders = (gcnew System::Windows::Forms::Button());
			this->btn_login = (gcnew System::Windows::Forms::Button());
			this->pn_picture = (gcnew System::Windows::Forms::Panel());
			this->lb_profile = (gcnew System::Windows::Forms::Label());
			this->pb_profile = (gcnew System::Windows::Forms::PictureBox());
			this->pn_thankyou = (gcnew System::Windows::Forms::Panel());
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->btn_exit = (gcnew System::Windows::Forms::Button());
			this->pn_login = (gcnew System::Windows::Forms::Panel());
			this->btn_register_loginpanel = (gcnew System::Windows::Forms::Button());
			this->btn_back_loginpanal = (gcnew System::Windows::Forms::Button());
			this->btn_login_loginpanel = (gcnew System::Windows::Forms::Button());
			this->pn_register = (gcnew System::Windows::Forms::Panel());
			this->pn_upper_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->BeginInit();
			this->pn_main_dashboard->SuspendLayout();
			this->pn_defualt->SuspendLayout();
			this->pn_products->SuspendLayout();
			this->panel11->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->pn_main_window->SuspendLayout();
			this->pn_edit_information->SuspendLayout();
			this->pn_blank->SuspendLayout();
			this->pn_orders->SuspendLayout();
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_picture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->BeginInit();
			this->pn_start->SuspendLayout();
			this->pn_login->SuspendLayout();
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
			this->pn_upper_bar->Name = L"pn_upper_bar";
			this->pn_upper_bar->Size = System::Drawing::Size(1500, 55);
			this->pn_upper_bar->TabIndex = 0;
			// 
			// lb_brand_name
			// 
			this->lb_brand_name->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_brand_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->lb_brand_name->Location = System::Drawing::Point(103, 9);
			this->lb_brand_name->Name = L"lb_brand_name";
			this->lb_brand_name->Size = System::Drawing::Size(191, 43);
			this->lb_brand_name->TabIndex = 4;
			this->lb_brand_name->Text = L"SuperMarko";
			// 
			// pb_icon
			// 
			this->pb_icon->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_icon.BackgroundImage")));
			this->pb_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->pb_icon->Location = System::Drawing::Point(3, 3);
			this->pb_icon->Name = L"pb_icon";
			this->pb_icon->Size = System::Drawing::Size(94, 50);
			this->pb_icon->TabIndex = 3;
			this->pb_icon->TabStop = false;
			// 
			// btn_minimize
			// 
			this->btn_minimize->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->btn_minimize->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_minimize.BackgroundImage")));
			this->btn_minimize->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_minimize->FlatAppearance->BorderSize = 0;
			this->btn_minimize->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->btn_minimize->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->btn_minimize->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_minimize->Location = System::Drawing::Point(1352, 5);
			this->btn_minimize->Margin = System::Windows::Forms::Padding(2);
			this->btn_minimize->Name = L"btn_minimize";
			this->btn_minimize->Size = System::Drawing::Size(65, 45);
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
			this->btn_close->FlatAppearance->MouseDownBackColor = System::Drawing::Color::White;
			this->btn_close->FlatAppearance->MouseOverBackColor = System::Drawing::Color::White;
			this->btn_close->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_close->Location = System::Drawing::Point(1415, 5);
			this->btn_close->Margin = System::Windows::Forms::Padding(5);
			this->btn_close->Name = L"btn_close";
			this->btn_close->Size = System::Drawing::Size(80, 45);
			this->btn_close->TabIndex = 1;
			this->btn_close->UseVisualStyleBackColor = true;
			this->btn_close->Click += gcnew System::EventHandler(this, &MyForm::btn_close_Click);
			// 
			// pn_main_dashboard
			// 
			this->pn_main_dashboard->Controls->Add(this->pn_defualt);
			this->pn_main_dashboard->Controls->Add(this->pn_start);
			this->pn_main_dashboard->Controls->Add(this->pn_thankyou);
			this->pn_main_dashboard->Controls->Add(this->pn_login);
			this->pn_main_dashboard->Controls->Add(this->pn_register);
			this->pn_main_dashboard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_dashboard->Location = System::Drawing::Point(0, 55);
			this->pn_main_dashboard->Name = L"pn_main_dashboard";
			this->pn_main_dashboard->Size = System::Drawing::Size(1500, 745);
			this->pn_main_dashboard->TabIndex = 1;
			// 
			// pn_defualt
			// 
			this->pn_defualt->Controls->Add(this->pn_products);
			this->pn_defualt->Controls->Add(this->pn_main_window);
			this->pn_defualt->Controls->Add(this->pn_edit_information);
			this->pn_defualt->Controls->Add(this->pn_blank);
			this->pn_defualt->Controls->Add(this->pn_orders);
			this->pn_defualt->Controls->Add(this->pn_left_bar);
			this->pn_defualt->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_defualt->Location = System::Drawing::Point(0, 0);
			this->pn_defualt->Name = L"pn_defualt";
			this->pn_defualt->Size = System::Drawing::Size(1500, 745);
			this->pn_defualt->TabIndex = 4;
			// 
			// pn_products
			// 
			this->pn_products->Controls->Add(this->panel11);
			this->pn_products->Controls->Add(this->pn_fruits);
			this->pn_products->Controls->Add(this->pn_vegetable);
			this->pn_products->Controls->Add(this->pn_dairy);
			this->pn_products->Controls->Add(this->pn_butcher_shop);
			this->pn_products->Controls->Add(this->pn_seafood);
			this->pn_products->Controls->Add(this->pn_);
			this->pn_products->Controls->Add(this->panel5);
			this->pn_products->Controls->Add(this->panel4);
			this->pn_products->Controls->Add(this->panel3);
			this->pn_products->Controls->Add(this->panel2);
			this->pn_products->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_products->Location = System::Drawing::Point(296, 0);
			this->pn_products->Name = L"pn_products";
			this->pn_products->Size = System::Drawing::Size(1204, 745);
			this->pn_products->TabIndex = 2;
			// 
			// panel11
			// 
			this->panel11->Controls->Add(this->flowLayoutPanel2);
			this->panel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel11->Location = System::Drawing::Point(0, 0);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(1204, 745);
			this->panel11->TabIndex = 14;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->flowLayoutPanel2->Controls->Add(this->btn_category_fruits);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_vegetable);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_dairy);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_butcher_shop);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_seafood);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_poultry);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_bakery);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_snacks);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_household);
			this->flowLayoutPanel2->Controls->Add(this->btn_category_pet_supplies);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(1204, 745);
			this->flowLayoutPanel2->TabIndex = 0;
			// 
			// btn_category_fruits
			// 
			this->btn_category_fruits->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_category_fruits->FlatAppearance->BorderSize = 0;
			this->btn_category_fruits->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_fruits->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_fruits->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_fruits.Image")));
			this->btn_category_fruits->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_fruits->Location = System::Drawing::Point(7, 7);
			this->btn_category_fruits->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_fruits->Name = L"btn_category_fruits";
			this->btn_category_fruits->Size = System::Drawing::Size(582, 135);
			this->btn_category_fruits->TabIndex = 0;
			this->btn_category_fruits->Text = L"Fresh Produce(fruits)";
			this->btn_category_fruits->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_fruits->UseVisualStyleBackColor = false;
			// 
			// btn_category_vegetable
			// 
			this->btn_category_vegetable->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->btn_category_vegetable->FlatAppearance->BorderSize = 0;
			this->btn_category_vegetable->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_vegetable->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_vegetable->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_vegetable.Image")));
			this->btn_category_vegetable->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_vegetable->Location = System::Drawing::Point(601, 7);
			this->btn_category_vegetable->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_vegetable->Name = L"btn_category_vegetable";
			this->btn_category_vegetable->Size = System::Drawing::Size(582, 135);
			this->btn_category_vegetable->TabIndex = 1;
			this->btn_category_vegetable->Text = L"Fresh Produce(vegetable)\r\n";
			this->btn_category_vegetable->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_vegetable->UseVisualStyleBackColor = false;
			// 
			// btn_category_dairy
			// 
			this->btn_category_dairy->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->btn_category_dairy->FlatAppearance->BorderSize = 0;
			this->btn_category_dairy->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_dairy->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_dairy->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_dairy.Image")));
			this->btn_category_dairy->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_dairy->Location = System::Drawing::Point(7, 154);
			this->btn_category_dairy->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_dairy->Name = L"btn_category_dairy";
			this->btn_category_dairy->Size = System::Drawing::Size(582, 135);
			this->btn_category_dairy->TabIndex = 2;
			this->btn_category_dairy->Text = L"Dairy and Eggs\r\n";
			this->btn_category_dairy->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_dairy->UseVisualStyleBackColor = false;
			// 
			// btn_category_butcher_shop
			// 
			this->btn_category_butcher_shop->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_category_butcher_shop->FlatAppearance->BorderSize = 0;
			this->btn_category_butcher_shop->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_butcher_shop->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_butcher_shop->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_butcher_shop.Image")));
			this->btn_category_butcher_shop->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_butcher_shop->Location = System::Drawing::Point(601, 154);
			this->btn_category_butcher_shop->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_butcher_shop->Name = L"btn_category_butcher_shop";
			this->btn_category_butcher_shop->Size = System::Drawing::Size(582, 135);
			this->btn_category_butcher_shop->TabIndex = 3;
			this->btn_category_butcher_shop->Text = L"Butcher Shop";
			this->btn_category_butcher_shop->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_butcher_shop->UseVisualStyleBackColor = false;
			// 
			// btn_category_seafood
			// 
			this->btn_category_seafood->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_category_seafood->FlatAppearance->BorderSize = 0;
			this->btn_category_seafood->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_seafood->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_seafood->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_seafood.Image")));
			this->btn_category_seafood->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_seafood->Location = System::Drawing::Point(7, 301);
			this->btn_category_seafood->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_seafood->Name = L"btn_category_seafood";
			this->btn_category_seafood->Size = System::Drawing::Size(582, 135);
			this->btn_category_seafood->TabIndex = 4;
			this->btn_category_seafood->Text = L"Seafood";
			this->btn_category_seafood->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_seafood->UseVisualStyleBackColor = false;
			// 
			// btn_category_poultry
			// 
			this->btn_category_poultry->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->btn_category_poultry->FlatAppearance->BorderSize = 0;
			this->btn_category_poultry->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_poultry->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_poultry->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_poultry.Image")));
			this->btn_category_poultry->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_poultry->Location = System::Drawing::Point(601, 301);
			this->btn_category_poultry->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_poultry->Name = L"btn_category_poultry";
			this->btn_category_poultry->Size = System::Drawing::Size(582, 135);
			this->btn_category_poultry->TabIndex = 5;
			this->btn_category_poultry->Text = L"Poultry";
			this->btn_category_poultry->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_poultry->UseVisualStyleBackColor = false;
			// 
			// btn_category_bakery
			// 
			this->btn_category_bakery->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->btn_category_bakery->FlatAppearance->BorderSize = 0;
			this->btn_category_bakery->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_bakery->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_bakery->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_bakery.Image")));
			this->btn_category_bakery->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_bakery->Location = System::Drawing::Point(7, 448);
			this->btn_category_bakery->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_bakery->Name = L"btn_category_bakery";
			this->btn_category_bakery->Size = System::Drawing::Size(582, 135);
			this->btn_category_bakery->TabIndex = 6;
			this->btn_category_bakery->Text = L"Bakery and Bread\r\n";
			this->btn_category_bakery->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_bakery->UseVisualStyleBackColor = false;
			// 
			// btn_category_snacks
			// 
			this->btn_category_snacks->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_category_snacks->FlatAppearance->BorderSize = 0;
			this->btn_category_snacks->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_snacks->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_snacks->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_snacks.Image")));
			this->btn_category_snacks->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_snacks->Location = System::Drawing::Point(601, 448);
			this->btn_category_snacks->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_snacks->Name = L"btn_category_snacks";
			this->btn_category_snacks->Size = System::Drawing::Size(582, 135);
			this->btn_category_snacks->TabIndex = 7;
			this->btn_category_snacks->Text = L"Snacks and Sweets      \r\n";
			this->btn_category_snacks->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_snacks->UseVisualStyleBackColor = false;
			// 
			// btn_category_household
			// 
			this->btn_category_household->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_category_household->FlatAppearance->BorderSize = 0;
			this->btn_category_household->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_household->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_household->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_household.Image")));
			this->btn_category_household->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_household->Location = System::Drawing::Point(7, 595);
			this->btn_category_household->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_household->Name = L"btn_category_household";
			this->btn_category_household->Size = System::Drawing::Size(582, 135);
			this->btn_category_household->TabIndex = 8;
			this->btn_category_household->Text = L"Household and Cleaning Supplies\r\n";
			this->btn_category_household->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_household->UseVisualStyleBackColor = false;
			this->btn_category_household->Click += gcnew System::EventHandler(this, &MyForm::button9_Click);
			// 
			// btn_category_pet_supplies
			// 
			this->btn_category_pet_supplies->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->btn_category_pet_supplies->FlatAppearance->BorderSize = 0;
			this->btn_category_pet_supplies->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_category_pet_supplies->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->btn_category_pet_supplies->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_category_pet_supplies.Image")));
			this->btn_category_pet_supplies->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->btn_category_pet_supplies->Location = System::Drawing::Point(601, 595);
			this->btn_category_pet_supplies->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->btn_category_pet_supplies->Name = L"btn_category_pet_supplies";
			this->btn_category_pet_supplies->Size = System::Drawing::Size(582, 135);
			this->btn_category_pet_supplies->TabIndex = 9;
			this->btn_category_pet_supplies->Text = L"Pet Supplies";
			this->btn_category_pet_supplies->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->btn_category_pet_supplies->UseVisualStyleBackColor = false;
			// 
			// pn_fruits
			// 
			this->pn_fruits->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_fruits->Location = System::Drawing::Point(0, 0);
			this->pn_fruits->Name = L"pn_fruits";
			this->pn_fruits->Size = System::Drawing::Size(1204, 745);
			this->pn_fruits->TabIndex = 4;
			// 
			// pn_vegetable
			// 
			this->pn_vegetable->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_vegetable->Location = System::Drawing::Point(0, 0);
			this->pn_vegetable->Name = L"pn_vegetable";
			this->pn_vegetable->Size = System::Drawing::Size(1204, 745);
			this->pn_vegetable->TabIndex = 13;
			// 
			// pn_dairy
			// 
			this->pn_dairy->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_dairy->Location = System::Drawing::Point(0, 0);
			this->pn_dairy->Name = L"pn_dairy";
			this->pn_dairy->Size = System::Drawing::Size(1204, 745);
			this->pn_dairy->TabIndex = 12;
			// 
			// pn_butcher_shop
			// 
			this->pn_butcher_shop->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_butcher_shop->Location = System::Drawing::Point(0, 0);
			this->pn_butcher_shop->Name = L"pn_butcher_shop";
			this->pn_butcher_shop->Size = System::Drawing::Size(1204, 745);
			this->pn_butcher_shop->TabIndex = 11;
			// 
			// pn_seafood
			// 
			this->pn_seafood->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_seafood->Location = System::Drawing::Point(0, 0);
			this->pn_seafood->Name = L"pn_seafood";
			this->pn_seafood->Size = System::Drawing::Size(1204, 745);
			this->pn_seafood->TabIndex = 10;
			// 
			// pn_
			// 
			this->pn_->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_->Location = System::Drawing::Point(0, 0);
			this->pn_->Name = L"pn_";
			this->pn_->Size = System::Drawing::Size(1204, 745);
			this->pn_->TabIndex = 9;
			// 
			// panel5
			// 
			this->panel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel5->Location = System::Drawing::Point(0, 0);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(1204, 745);
			this->panel5->TabIndex = 8;
			// 
			// panel4
			// 
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1204, 745);
			this->panel4->TabIndex = 7;
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1204, 745);
			this->panel3->TabIndex = 6;
			// 
			// panel2
			// 
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1204, 745);
			this->panel2->TabIndex = 5;
			// 
			// pn_main_window
			// 
			this->pn_main_window->Controls->Add(this->label5);
			this->pn_main_window->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_window->Location = System::Drawing::Point(296, 0);
			this->pn_main_window->Name = L"pn_main_window";
			this->pn_main_window->Size = System::Drawing::Size(1204, 745);
			this->pn_main_window->TabIndex = 5;
			// 
			// label5
			// 
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(270, 169);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(663, 151);
			this->label5->TabIndex = 0;
			this->label5->Text = L"main";
			// 
			// pn_edit_information
			// 
			this->pn_edit_information->Controls->Add(this->label1);
			this->pn_edit_information->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_edit_information->Location = System::Drawing::Point(296, 0);
			this->pn_edit_information->Name = L"pn_edit_information";
			this->pn_edit_information->Size = System::Drawing::Size(1204, 745);
			this->pn_edit_information->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(270, 169);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(663, 151);
			this->label1->TabIndex = 0;
			this->label1->Text = L"edit information";
			// 
			// pn_blank
			// 
			this->pn_blank->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_blank->Controls->Add(this->label4);
			this->pn_blank->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_blank->Location = System::Drawing::Point(296, 0);
			this->pn_blank->Name = L"pn_blank";
			this->pn_blank->Size = System::Drawing::Size(1204, 745);
			this->pn_blank->TabIndex = 4;
			// 
			// label4
			// 
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(271, 297);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(663, 151);
			this->label4->TabIndex = 1;
			this->label4->Text = L"blank";
			// 
			// pn_orders
			// 
			this->pn_orders->Controls->Add(this->label2);
			this->pn_orders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_orders->Location = System::Drawing::Point(296, 0);
			this->pn_orders->Name = L"pn_orders";
			this->pn_orders->Size = System::Drawing::Size(1204, 745);
			this->pn_orders->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(271, 297);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(663, 151);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Order";
			// 
			// pn_left_bar
			// 
			this->pn_left_bar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(51)), static_cast<System::Int32>(static_cast<System::Byte>(55)),
				static_cast<System::Int32>(static_cast<System::Byte>(69)));
			this->pn_left_bar->Controls->Add(this->flowLayoutPanel1);
			this->pn_left_bar->Controls->Add(this->pn_picture);
			this->pn_left_bar->Dock = System::Windows::Forms::DockStyle::Left;
			this->pn_left_bar->Location = System::Drawing::Point(0, 0);
			this->pn_left_bar->Name = L"pn_left_bar";
			this->pn_left_bar->Size = System::Drawing::Size(296, 745);
			this->pn_left_bar->TabIndex = 0;
			// 
			// flowLayoutPanel1
			// 
			this->flowLayoutPanel1->Controls->Add(this->btn_edit_information);
			this->flowLayoutPanel1->Controls->Add(this->btn_products);
			this->flowLayoutPanel1->Controls->Add(this->btn_orders);
			this->flowLayoutPanel1->Controls->Add(this->btn_login);
			this->flowLayoutPanel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel1->Location = System::Drawing::Point(0, 201);
			this->flowLayoutPanel1->Name = L"flowLayoutPanel1";
			this->flowLayoutPanel1->Size = System::Drawing::Size(296, 544);
			this->flowLayoutPanel1->TabIndex = 1;
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
			this->btn_edit_information->Location = System::Drawing::Point(2, 20);
			this->btn_edit_information->Margin = System::Windows::Forms::Padding(2, 20, 2, 2);
			this->btn_edit_information->Name = L"btn_edit_information";
			this->btn_edit_information->Size = System::Drawing::Size(293, 99);
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
			this->btn_products->Location = System::Drawing::Point(3, 141);
			this->btn_products->Margin = System::Windows::Forms::Padding(3, 20, 3, 3);
			this->btn_products->Name = L"btn_products";
			this->btn_products->Size = System::Drawing::Size(293, 99);
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
			this->btn_orders->Location = System::Drawing::Point(3, 263);
			this->btn_orders->Margin = System::Windows::Forms::Padding(3, 20, 3, 3);
			this->btn_orders->Name = L"btn_orders";
			this->btn_orders->Size = System::Drawing::Size(293, 99);
			this->btn_orders->TabIndex = 2;
			this->btn_orders->Text = L"Orders";
			this->btn_orders->UseVisualStyleBackColor = true;
			this->btn_orders->Click += gcnew System::EventHandler(this, &MyForm::btn_orders_Click);
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
			this->btn_login->Location = System::Drawing::Point(3, 450);
			this->btn_login->Margin = System::Windows::Forms::Padding(3, 85, 3, 3);
			this->btn_login->Name = L"btn_login";
			this->btn_login->Size = System::Drawing::Size(293, 99);
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
			this->pn_picture->Name = L"pn_picture";
			this->pn_picture->Size = System::Drawing::Size(296, 201);
			this->pn_picture->TabIndex = 0;
			// 
			// lb_profile
			// 
			this->lb_profile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_profile->Location = System::Drawing::Point(38, 109);
			this->lb_profile->Name = L"lb_profile";
			this->lb_profile->Size = System::Drawing::Size(198, 23);
			this->lb_profile->TabIndex = 1;
			this->lb_profile->Text = L"label2";
			// 
			// pb_profile
			// 
			this->pb_profile->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_profile.BackgroundImage")));
			this->pb_profile->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->pb_profile->Location = System::Drawing::Point(38, 6);
			this->pb_profile->Name = L"pb_profile";
			this->pb_profile->Size = System::Drawing::Size(198, 89);
			this->pb_profile->TabIndex = 0;
			this->pb_profile->TabStop = false;
			// 
			// pn_thankyou
			// 
			this->pn_thankyou->Location = System::Drawing::Point(0, 0);
			this->pn_thankyou->Name = L"pn_thankyou";
			this->pn_thankyou->Size = System::Drawing::Size(1500, 745);
			this->pn_thankyou->TabIndex = 0;
			// 
			// pn_start
			// 
			this->pn_start->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->pn_start->Controls->Add(this->btn_start);
			this->pn_start->Controls->Add(this->btn_exit);
			this->pn_start->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_start->Location = System::Drawing::Point(0, 0);
			this->pn_start->Name = L"pn_start";
			this->pn_start->Size = System::Drawing::Size(1500, 745);
			this->pn_start->TabIndex = 3;
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
			this->btn_start->Location = System::Drawing::Point(1136, 640);
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
			this->btn_exit->Location = System::Drawing::Point(98, 640);
			this->btn_exit->Name = L"btn_exit";
			this->btn_exit->Size = System::Drawing::Size(225, 52);
			this->btn_exit->TabIndex = 0;
			this->btn_exit->Text = L"Exit";
			this->btn_exit->UseVisualStyleBackColor = false;
			this->btn_exit->Click += gcnew System::EventHandler(this, &MyForm::btn_exit_Click);
			this->btn_exit->MouseEnter += gcnew System::EventHandler(this, &MyForm::btn_exit_MouseEnter);
			this->btn_exit->MouseLeave += gcnew System::EventHandler(this, &MyForm::btn_exit_MouseLeave);
			// 
			// pn_login
			// 
			this->pn_login->Controls->Add(this->btn_register_loginpanel);
			this->pn_login->Controls->Add(this->btn_back_loginpanal);
			this->pn_login->Controls->Add(this->btn_login_loginpanel);
			this->pn_login->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_login->Location = System::Drawing::Point(0, 0);
			this->pn_login->Name = L"pn_login";
			this->pn_login->Size = System::Drawing::Size(1500, 745);
			this->pn_login->TabIndex = 2;
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
			this->btn_register_loginpanel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_register_loginpanel->Location = System::Drawing::Point(109, 634);
			this->btn_register_loginpanel->Name = L"btn_register_loginpanel";
			this->btn_register_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_register_loginpanel->TabIndex = 2;
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
			this->btn_back_loginpanal->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_back_loginpanal->Location = System::Drawing::Point(950, 634);
			this->btn_back_loginpanal->Name = L"btn_back_loginpanal";
			this->btn_back_loginpanal->Size = System::Drawing::Size(229, 58);
			this->btn_back_loginpanal->TabIndex = 1;
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
			this->btn_login_loginpanel->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)), static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->btn_login_loginpanel->Location = System::Drawing::Point(109, 283);
			this->btn_login_loginpanel->Name = L"btn_login_loginpanel";
			this->btn_login_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_login_loginpanel->TabIndex = 0;
			this->btn_login_loginpanel->Text = L"Log in";
			this->btn_login_loginpanel->UseVisualStyleBackColor = false;
			// 
			// pn_register
			// 
			this->pn_register->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_register->Location = System::Drawing::Point(0, 0);
			this->pn_register->Name = L"pn_register";
			this->pn_register->Size = System::Drawing::Size(1500, 745);
			this->pn_register->TabIndex = 1;
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1500, 800);
			this->Controls->Add(this->pn_main_dashboard);
			this->Controls->Add(this->pn_upper_bar);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"MyForm";
			this->Text = L"SuperMarko";
			this->pn_upper_bar->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->EndInit();
			this->pn_main_dashboard->ResumeLayout(false);
			this->pn_defualt->ResumeLayout(false);
			this->pn_products->ResumeLayout(false);
			this->panel11->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->pn_main_window->ResumeLayout(false);
			this->pn_edit_information->ResumeLayout(false);
			this->pn_blank->ResumeLayout(false);
			this->pn_orders->ResumeLayout(false);
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_picture->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->EndInit();
			this->pn_start->ResumeLayout(false);
			this->pn_login->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btn_close_Click(System::Object^ sender, System::EventArgs^ e) {
		Application::Exit();	
	}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->WindowState = FormWindowState::Minimized;
}
private: System::Void btn_edit_information_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_edit_information->BringToFront();	
}
private: System::Void btn_products_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_products->BringToFront();	
}
private: System::Void btn_orders_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_orders->BringToFront();	
}
private: System::Void btn_login_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_login->BringToFront();
}
private: System::Void btn_exit_MouseEnter(System::Object^ sender, System::EventArgs^ e) {
	btn_exit->ForeColor = Color::FromArgb(0xE6, 0x34, 0x62);
}
private: System::Void btn_exit_MouseLeave(System::Object^ sender, System::EventArgs^ e) {
	btn_exit->ForeColor = Color::Black;

}
private: System::Void btn_exit_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_thankyou->BringToFront();	
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
	pn_login->BringToFront();
}
private: System::Void btn_back_loginpanal_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_start->BringToFront();
}
private: System::Void btn_register_loginpanel_Click(System::Object^ sender, System::EventArgs^ e) {
	pn_register->BringToFront();
}
private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e) {
}
};
}
