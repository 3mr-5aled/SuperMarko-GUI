#pragma once


namespace SuperMarkoGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
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



	private: System::Windows::Forms::Panel^ panel11;
	private: System::Windows::Forms::FlowLayoutPanel^ flowLayoutPanel2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button9;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::PictureBox^ welcomeScreen;

	private: System::Windows::Forms::PictureBox^ thankyou;










	private: System::Windows::Forms::Button^ btn_category_household;
	private: System::Windows::Forms::Button^ btn_category_pet_supplies;
private: System::Windows::Forms::Panel^ panel10;
private: System::Windows::Forms::Panel^ panel9;
private: System::Windows::Forms::Panel^ panel8;
private: System::Windows::Forms::Panel^ panel7;
private: System::Windows::Forms::Panel^ panel6;
private: System::Windows::Forms::Panel^ panel1;
private: System::Windows::Forms::TextBox^ tb_password;
private: System::Windows::Forms::TextBox^ tb_username;
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
			this->pn_register = (gcnew System::Windows::Forms::Panel());
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
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->btn_start = (gcnew System::Windows::Forms::Button());
			this->btn_exit = (gcnew System::Windows::Forms::Button());
			this->welcomeScreen = (gcnew System::Windows::Forms::PictureBox());
			this->pn_thankyou = (gcnew System::Windows::Forms::Panel());
			this->thankyou = (gcnew System::Windows::Forms::PictureBox());
			this->pn_defualt = (gcnew System::Windows::Forms::Panel());
			this->pn_blank = (gcnew System::Windows::Forms::Panel());
			this->pb_blankpicutre = (gcnew System::Windows::Forms::PictureBox());
			this->pn_products = (gcnew System::Windows::Forms::Panel());
			this->panel11 = (gcnew System::Windows::Forms::Panel());
			this->panel10 = (gcnew System::Windows::Forms::Panel());
			this->panel9 = (gcnew System::Windows::Forms::Panel());
			this->panel8 = (gcnew System::Windows::Forms::Panel());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel2 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->pn_edit_information = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
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
			this->pn_login = (gcnew System::Windows::Forms::Panel());
			this->tb_password = (gcnew System::Windows::Forms::TextBox());
			this->tb_username = (gcnew System::Windows::Forms::TextBox());
			this->lb_password = (gcnew System::Windows::Forms::Label());
			this->lb_username = (gcnew System::Windows::Forms::Label());
			this->btn_register_loginpanel = (gcnew System::Windows::Forms::Button());
			this->btn_back_loginpanal = (gcnew System::Windows::Forms::Button());
			this->btn_login_loginpanel = (gcnew System::Windows::Forms::Button());
			this->pn_upper_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->BeginInit();
			this->pn_main_dashboard->SuspendLayout();
			this->pn_register->SuspendLayout();
			this->pn_start->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->BeginInit();
			this->pn_thankyou->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thankyou))->BeginInit();
			this->pn_defualt->SuspendLayout();
			this->pn_blank->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->BeginInit();
			this->pn_products->SuspendLayout();
			this->panel11->SuspendLayout();
			this->flowLayoutPanel2->SuspendLayout();
			this->pn_edit_information->SuspendLayout();
			this->pn_orders->SuspendLayout();
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_picture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->BeginInit();
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
			this->pn_upper_bar->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_upper_bar->Name = L"pn_upper_bar";
			this->pn_upper_bar->Size = System::Drawing::Size(1500, 55);
			this->pn_upper_bar->TabIndex = 0;
			// 
			// lb_brand_name
			// 
			this->lb_brand_name->Font = (gcnew System::Drawing::Font(L"Segoe UI", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_brand_name->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->lb_brand_name->Location = System::Drawing::Point(103, 9);
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
			this->btn_minimize->Location = System::Drawing::Point(1358, 5);
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
			this->btn_close->Location = System::Drawing::Point(1415, 5);
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
			this->pn_main_dashboard->Controls->Add(this->pn_register);
			this->pn_main_dashboard->Controls->Add(this->pn_thankyou);
			this->pn_main_dashboard->Controls->Add(this->pn_defualt);
			this->pn_main_dashboard->Controls->Add(this->pn_login);
			this->pn_main_dashboard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_dashboard->Location = System::Drawing::Point(0, 55);
			this->pn_main_dashboard->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_main_dashboard->Name = L"pn_main_dashboard";
			this->pn_main_dashboard->Size = System::Drawing::Size(1500, 745);
			this->pn_main_dashboard->TabIndex = 1;
			// 
			// pn_register
			// 
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
			this->pn_register->Size = System::Drawing::Size(1500, 745);
			this->pn_register->TabIndex = 1;
			// 
			// btn_refresh_location_register
			// 
			this->btn_refresh_location_register->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"btn_refresh_location_register.BackgroundImage")));
			this->btn_refresh_location_register->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			this->btn_refresh_location_register->FlatAppearance->BorderSize = 0;
			this->btn_refresh_location_register->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btn_refresh_location_register->Location = System::Drawing::Point(668, 352);
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
			this->btn_refresh_phonenumber_register->Location = System::Drawing::Point(668, 255);
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
			this->btn_refresh_password_register->Location = System::Drawing::Point(668, 169);
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
			this->btn_refresh_username_register->Location = System::Drawing::Point(668, 78);
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
			this->btn_seepassword->Location = System::Drawing::Point(601, 170);
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
			this->link_login->Location = System::Drawing::Point(290, 616);
			this->link_login->Name = L"link_login";
			this->link_login->Size = System::Drawing::Size(270, 36);
			this->link_login->TabIndex = 13;
			this->link_login->TabStop = true;
			this->link_login->Text = L"login";
			this->link_login->LinkClicked += gcnew System::Windows::Forms::LinkLabelLinkClickedEventHandler(this, &MyForm::linklogin_LinkClicked);
			// 
			// lb_location_message
			// 
			this->lb_location_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_location_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_location_message->Location = System::Drawing::Point(337, 378);
			this->lb_location_message->Name = L"lb_location_message";
			this->lb_location_message->Size = System::Drawing::Size(325, 23);
			this->lb_location_message->TabIndex = 12;
			this->lb_location_message->Text = L"Enter the location";
			// 
			// lb_phonenumber_message
			// 
			this->lb_phonenumber_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_phonenumber_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_phonenumber_message->Location = System::Drawing::Point(337, 281);
			this->lb_phonenumber_message->Name = L"lb_phonenumber_message";
			this->lb_phonenumber_message->Size = System::Drawing::Size(325, 23);
			this->lb_phonenumber_message->TabIndex = 11;
			this->lb_phonenumber_message->Text = L"Enter the phone number";
			// 
			// lb_password_message
			// 
			this->lb_password_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_password_message->Location = System::Drawing::Point(337, 195);
			this->lb_password_message->Name = L"lb_password_message";
			this->lb_password_message->Size = System::Drawing::Size(325, 23);
			this->lb_password_message->TabIndex = 10;
			this->lb_password_message->Text = L"Enter the password";
			// 
			// lb_username_message
			// 
			this->lb_username_message->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_message->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)),
				static_cast<System::Int32>(static_cast<System::Byte>(95)), static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->lb_username_message->Location = System::Drawing::Point(337, 104);
			this->lb_username_message->Name = L"lb_username_message";
			this->lb_username_message->Size = System::Drawing::Size(325, 23);
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
			this->btn_register_registerpanel->Location = System::Drawing::Point(110, 549);
			this->btn_register_registerpanel->Name = L"btn_register_registerpanel";
			this->btn_register_registerpanel->Size = System::Drawing::Size(244, 64);
			this->btn_register_registerpanel->TabIndex = 8;
			this->btn_register_registerpanel->Text = L"Register";
			this->btn_register_registerpanel->UseVisualStyleBackColor = false;
			this->btn_register_registerpanel->Click += gcnew System::EventHandler(this, &MyForm::btn_register_registerpanel_Click);
			// 
			// tb_location_register
			// 
			this->tb_location_register->Location = System::Drawing::Point(337, 353);
			this->tb_location_register->Name = L"tb_location_register";
			this->tb_location_register->Size = System::Drawing::Size(325, 22);
			this->tb_location_register->TabIndex = 7;
			// 
			// tb_phonenumber_register
			// 
			this->tb_phonenumber_register->Location = System::Drawing::Point(337, 256);
			this->tb_phonenumber_register->Name = L"tb_phonenumber_register";
			this->tb_phonenumber_register->Size = System::Drawing::Size(325, 22);
			this->tb_phonenumber_register->TabIndex = 6;
			// 
			// tb_password_register
			// 
			this->tb_password_register->Location = System::Drawing::Point(337, 170);
			this->tb_password_register->Name = L"tb_password_register";
			this->tb_password_register->Size = System::Drawing::Size(325, 22);
			this->tb_password_register->TabIndex = 5;
			this->tb_password_register->UseSystemPasswordChar = true;
			// 
			// tb_username_register
			// 
			this->tb_username_register->Location = System::Drawing::Point(337, 79);
			this->tb_username_register->Name = L"tb_username_register";
			this->tb_username_register->Size = System::Drawing::Size(325, 22);
			this->tb_username_register->TabIndex = 4;
			this->tb_username_register->TextChanged += gcnew System::EventHandler(this, &MyForm::tb_username_username_TextChanged);
			// 
			// lb_password_register
			// 
			this->lb_password_register->AutoSize = true;
			this->lb_password_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_password_register->Location = System::Drawing::Point(82, 160);
			this->lb_password_register->Name = L"lb_password_register";
			this->lb_password_register->Size = System::Drawing::Size(153, 32);
			this->lb_password_register->TabIndex = 3;
			this->lb_password_register->Text = L"Password :";
			// 
			// lb_phonenumber_register
			// 
			this->lb_phonenumber_register->AutoSize = true;
			this->lb_phonenumber_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_phonenumber_register->Location = System::Drawing::Point(82, 249);
			this->lb_phonenumber_register->Name = L"lb_phonenumber_register";
			this->lb_phonenumber_register->Size = System::Drawing::Size(215, 32);
			this->lb_phonenumber_register->TabIndex = 2;
			this->lb_phonenumber_register->Text = L"Phone number :";
			// 
			// lb_location
			// 
			this->lb_location->AutoSize = true;
			this->lb_location->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_location->Location = System::Drawing::Point(82, 343);
			this->lb_location->Name = L"lb_location";
			this->lb_location->Size = System::Drawing::Size(138, 32);
			this->lb_location->TabIndex = 1;
			this->lb_location->Text = L"Location :";
			// 
			// lb_username_register
			// 
			this->lb_username_register->AutoSize = true;
			this->lb_username_register->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->lb_username_register->Location = System::Drawing::Point(82, 69);
			this->lb_username_register->Name = L"lb_username_register";
			this->lb_username_register->Size = System::Drawing::Size(159, 32);
			this->lb_username_register->TabIndex = 0;
			this->lb_username_register->Text = L"Username :";
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
			this->welcomeScreen->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"welcomeScreen.BackgroundImage")));
			this->welcomeScreen->BackgroundImageLayout = System::Windows::Forms::ImageLayout::None;
			this->welcomeScreen->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"welcomeScreen.Image")));
			this->welcomeScreen->Location = System::Drawing::Point(0, 0);
			this->welcomeScreen->Margin = System::Windows::Forms::Padding(4);
			this->welcomeScreen->Name = L"welcomeScreen";
			this->welcomeScreen->Size = System::Drawing::Size(1500, 745);
			this->welcomeScreen->TabIndex = 2;
			this->welcomeScreen->TabStop = false;
			// 
			// pn_thankyou
			// 
			this->pn_thankyou->Controls->Add(this->thankyou);
			this->pn_thankyou->Location = System::Drawing::Point(0, 0);
			this->pn_thankyou->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_thankyou->Name = L"pn_thankyou";
			this->pn_thankyou->Size = System::Drawing::Size(1500, 745);
			this->pn_thankyou->TabIndex = 0;
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
			// 
			// pn_defualt
			// 
			this->pn_defualt->Controls->Add(this->pn_blank);
			this->pn_defualt->Controls->Add(this->pn_products);
			this->pn_defualt->Controls->Add(this->pn_edit_information);
			this->pn_defualt->Controls->Add(this->pn_orders);
			this->pn_defualt->Controls->Add(this->pn_left_bar);
			this->pn_defualt->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_defualt->Location = System::Drawing::Point(0, 0);
			this->pn_defualt->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_defualt->Name = L"pn_defualt";
			this->pn_defualt->Size = System::Drawing::Size(1500, 745);
			this->pn_defualt->TabIndex = 4;
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
			this->pn_blank->Size = System::Drawing::Size(1204, 745);
			this->pn_blank->TabIndex = 4;
			// 
			// pb_blankpicutre
			// 
			this->pb_blankpicutre->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pb_blankpicutre.BackgroundImage")));
			this->pb_blankpicutre->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->pb_blankpicutre->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pb_blankpicutre->Location = System::Drawing::Point(0, 0);
			this->pb_blankpicutre->Name = L"pb_blankpicutre";
			this->pb_blankpicutre->Size = System::Drawing::Size(1204, 745);
			this->pb_blankpicutre->TabIndex = 2;
			this->pb_blankpicutre->TabStop = false;
			// 
			// pn_products
			// 
			this->pn_products->Controls->Add(this->panel11);
			this->pn_products->Controls->Add(this->panel5);
			this->pn_products->Controls->Add(this->panel4);
			this->pn_products->Controls->Add(this->panel3);
			this->pn_products->Controls->Add(this->panel2);
			this->pn_products->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_products->Location = System::Drawing::Point(296, 0);
			this->pn_products->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_products->Name = L"pn_products";
			this->pn_products->Size = System::Drawing::Size(1204, 745);
			this->pn_products->TabIndex = 2;
			// 
			// panel11
			// 
			this->panel11->Controls->Add(this->panel10);
			this->panel11->Controls->Add(this->panel9);
			this->panel11->Controls->Add(this->panel8);
			this->panel11->Controls->Add(this->panel7);
			this->panel11->Controls->Add(this->panel6);
			this->panel11->Controls->Add(this->panel1);
			this->panel11->Controls->Add(this->flowLayoutPanel2);
			this->panel11->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel11->Location = System::Drawing::Point(0, 0);
			this->panel11->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel11->Name = L"panel11";
			this->panel11->Size = System::Drawing::Size(1204, 745);
			this->panel11->TabIndex = 14;
			// 
			// panel10
			// 
			this->panel10->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel10->Location = System::Drawing::Point(0, 0);
			this->panel10->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel10->Name = L"panel10";
			this->panel10->Size = System::Drawing::Size(1204, 745);
			this->panel10->TabIndex = 11;
			// 
			// panel9
			// 
			this->panel9->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel9->Location = System::Drawing::Point(0, 0);
			this->panel9->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel9->Name = L"panel9";
			this->panel9->Size = System::Drawing::Size(1204, 745);
			this->panel9->TabIndex = 10;
			// 
			// panel8
			// 
			this->panel8->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel8->Location = System::Drawing::Point(0, 0);
			this->panel8->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel8->Name = L"panel8";
			this->panel8->Size = System::Drawing::Size(1204, 745);
			this->panel8->TabIndex = 9;
			// 
			// panel7
			// 
			this->panel7->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel7->Location = System::Drawing::Point(0, 0);
			this->panel7->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(1204, 745);
			this->panel7->TabIndex = 8;
			// 
			// panel6
			// 
			this->panel6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel6->Location = System::Drawing::Point(0, 0);
			this->panel6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(1204, 745);
			this->panel6->TabIndex = 7;
			// 
			// panel1
			// 
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1204, 745);
			this->panel1->TabIndex = 6;
			// 
			// flowLayoutPanel2
			// 
			this->flowLayoutPanel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(239)),
				static_cast<System::Int32>(static_cast<System::Byte>(239)), static_cast<System::Int32>(static_cast<System::Byte>(230)));
			this->flowLayoutPanel2->Controls->Add(this->button1);
			this->flowLayoutPanel2->Controls->Add(this->button2);
			this->flowLayoutPanel2->Controls->Add(this->button3);
			this->flowLayoutPanel2->Controls->Add(this->button4);
			this->flowLayoutPanel2->Controls->Add(this->button5);
			this->flowLayoutPanel2->Controls->Add(this->button6);
			this->flowLayoutPanel2->Controls->Add(this->button7);
			this->flowLayoutPanel2->Controls->Add(this->button8);
			this->flowLayoutPanel2->Controls->Add(this->button9);
			this->flowLayoutPanel2->Controls->Add(this->button10);
			this->flowLayoutPanel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->flowLayoutPanel2->Location = System::Drawing::Point(0, 0);
			this->flowLayoutPanel2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->flowLayoutPanel2->Name = L"flowLayoutPanel2";
			this->flowLayoutPanel2->Size = System::Drawing::Size(1204, 745);
			this->flowLayoutPanel2->TabIndex = 0;
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button1->FlatAppearance->BorderSize = 0;
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button1->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button1->Location = System::Drawing::Point(7, 7);
			this->button1->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(581, 135);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Fresh Produce(fruits)";
			this->button1->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button1->UseVisualStyleBackColor = false;
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(95)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->button2->FlatAppearance->BorderSize = 0;
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button2->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button2->Location = System::Drawing::Point(600, 7);
			this->button2->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(581, 135);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Fresh Produce(fruits)";
			this->button2->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button2->UseVisualStyleBackColor = false;
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(95)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->button3->FlatAppearance->BorderSize = 0;
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button3->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button3->Location = System::Drawing::Point(7, 154);
			this->button3->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(581, 135);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Fresh Produce(fruits)";
			this->button3->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button3->UseVisualStyleBackColor = false;
			// 
			// button4
			// 
			this->button4->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button4->Location = System::Drawing::Point(600, 154);
			this->button4->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(581, 135);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Fresh Produce(fruits)";
			this->button4->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button4->UseVisualStyleBackColor = false;
			// 
			// button5
			// 
			this->button5->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button5->Location = System::Drawing::Point(7, 301);
			this->button5->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(581, 135);
			this->button5->TabIndex = 4;
			this->button5->Text = L"Fresh Produce(fruits)";
			this->button5->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button5->UseVisualStyleBackColor = false;
			// 
			// button6
			// 
			this->button6->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(95)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button6->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button6->Location = System::Drawing::Point(600, 301);
			this->button6->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(581, 135);
			this->button6->TabIndex = 5;
			this->button6->Text = L"Fresh Produce(fruits)";
			this->button6->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button6->UseVisualStyleBackColor = false;
			// 
			// button7
			// 
			this->button7->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(95)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->button7->FlatAppearance->BorderSize = 0;
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button7->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button7->Location = System::Drawing::Point(7, 448);
			this->button7->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(581, 135);
			this->button7->TabIndex = 6;
			this->button7->Text = L"Fresh Produce(fruits)";
			this->button7->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button7->UseVisualStyleBackColor = false;
			// 
			// button8
			// 
			this->button8->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button8->FlatAppearance->BorderSize = 0;
			this->button8->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button8->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button8->Location = System::Drawing::Point(600, 448);
			this->button8->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(581, 135);
			this->button8->TabIndex = 7;
			this->button8->Text = L"Fresh Produce(fruits)";
			this->button8->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button8->UseVisualStyleBackColor = false;
			// 
			// button9
			// 
			this->button9->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(230)), static_cast<System::Int32>(static_cast<System::Byte>(52)),
				static_cast<System::Int32>(static_cast<System::Byte>(98)));
			this->button9->FlatAppearance->BorderSize = 0;
			this->button9->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button9->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button9->Location = System::Drawing::Point(7, 595);
			this->button9->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(581, 135);
			this->button9->TabIndex = 8;
			this->button9->Text = L"Fresh Produce(fruits)";
			this->button9->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button9->UseVisualStyleBackColor = false;
			// 
			// button10
			// 
			this->button10->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(254)), static_cast<System::Int32>(static_cast<System::Byte>(95)),
				static_cast<System::Int32>(static_cast<System::Byte>(85)));
			this->button10->FlatAppearance->BorderSize = 0;
			this->button10->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->button10->ImageAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->button10->Location = System::Drawing::Point(600, 595);
			this->button10->Margin = System::Windows::Forms::Padding(7, 7, 5, 5);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(581, 135);
			this->button10->TabIndex = 9;
			this->button10->Text = L"Fresh Produce(fruits)";
			this->button10->TextAlign = System::Drawing::ContentAlignment::MiddleLeft;
			this->button10->UseVisualStyleBackColor = false;
			// 
			// panel5
			// 
			this->panel5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel5->Location = System::Drawing::Point(0, 0);
			this->panel5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(1204, 745);
			this->panel5->TabIndex = 8;
			// 
			// panel4
			// 
			this->panel4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel4->Location = System::Drawing::Point(0, 0);
			this->panel4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(1204, 745);
			this->panel4->TabIndex = 7;
			// 
			// panel3
			// 
			this->panel3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel3->Location = System::Drawing::Point(0, 0);
			this->panel3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(1204, 745);
			this->panel3->TabIndex = 6;
			// 
			// panel2
			// 
			this->panel2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel2->Location = System::Drawing::Point(0, 0);
			this->panel2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(1204, 745);
			this->panel2->TabIndex = 5;
			// 
			// pn_edit_information
			// 
			this->pn_edit_information->Controls->Add(this->label1);
			this->pn_edit_information->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_edit_information->Location = System::Drawing::Point(296, 0);
			this->pn_edit_information->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_edit_information->Name = L"pn_edit_information";
			this->pn_edit_information->Size = System::Drawing::Size(1204, 745);
			this->pn_edit_information->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(269, 169);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(663, 151);
			this->label1->TabIndex = 0;
			this->label1->Text = L"edit information";
			// 
			// pn_orders
			// 
			this->pn_orders->Controls->Add(this->label2);
			this->pn_orders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_orders->Location = System::Drawing::Point(296, 0);
			this->pn_orders->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->btn_edit_information->Size = System::Drawing::Size(293, 98);
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
			this->btn_products->Location = System::Drawing::Point(3, 140);
			this->btn_products->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_products->Name = L"btn_products";
			this->btn_products->Size = System::Drawing::Size(293, 98);
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
			this->btn_orders->Location = System::Drawing::Point(3, 260);
			this->btn_orders->Margin = System::Windows::Forms::Padding(3, 20, 3, 2);
			this->btn_orders->Name = L"btn_orders";
			this->btn_orders->Size = System::Drawing::Size(293, 98);
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
			this->btn_login->Location = System::Drawing::Point(3, 445);
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
			// 
			// lb_profile
			// 
			this->lb_profile->BackColor = System::Drawing::Color::Transparent;
			this->lb_profile->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_profile->ForeColor = System::Drawing::Color::White;
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
			// 
			// pn_login
			// 
			this->pn_login->Controls->Add(this->tb_password);
			this->pn_login->Controls->Add(this->tb_username);
			this->pn_login->Controls->Add(this->lb_password);
			this->pn_login->Controls->Add(this->lb_username);
			this->pn_login->Controls->Add(this->btn_register_loginpanel);
			this->pn_login->Controls->Add(this->btn_back_loginpanal);
			this->pn_login->Controls->Add(this->btn_login_loginpanel);
			this->pn_login->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_login->Location = System::Drawing::Point(0, 0);
			this->pn_login->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->pn_login->Name = L"pn_login";
			this->pn_login->Size = System::Drawing::Size(1500, 745);
			this->pn_login->TabIndex = 2;
			// 
			// tb_password
			// 
			this->tb_password->Location = System::Drawing::Point(174, 129);
			this->tb_password->Name = L"tb_password";
			this->tb_password->Size = System::Drawing::Size(330, 22);
			this->tb_password->TabIndex = 6;
			this->tb_password->UseSystemPasswordChar = true;
			// 
			// tb_username
			// 
			this->tb_username->Location = System::Drawing::Point(174, 68);
			this->tb_username->Name = L"tb_username";
			this->tb_username->Size = System::Drawing::Size(330, 22);
			this->tb_username->TabIndex = 5;
			// 
			// lb_password
			// 
			this->lb_password->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_password->Location = System::Drawing::Point(42, 122);
			this->lb_password->Name = L"lb_password";
			this->lb_password->Size = System::Drawing::Size(154, 34);
			this->lb_password->TabIndex = 4;
			this->lb_password->Text = L"Password";
			// 
			// lb_username
			// 
			this->lb_username->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.8F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lb_username->Location = System::Drawing::Point(42, 61);
			this->lb_username->Name = L"lb_username";
			this->lb_username->Size = System::Drawing::Size(154, 34);
			this->lb_username->TabIndex = 3;
			this->lb_username->Text = L"Username";
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
			this->btn_register_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->btn_back_loginpanal->Location = System::Drawing::Point(949, 634);
			this->btn_back_loginpanal->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
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
			this->btn_login_loginpanel->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->btn_login_loginpanel->Name = L"btn_login_loginpanel";
			this->btn_login_loginpanel->Size = System::Drawing::Size(229, 58);
			this->btn_login_loginpanel->TabIndex = 0;
			this->btn_login_loginpanel->Text = L"Log in";
			this->btn_login_loginpanel->UseVisualStyleBackColor = false;
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
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"MyForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"SuperMarko";
			this->pn_upper_bar->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->EndInit();
			this->pn_main_dashboard->ResumeLayout(false);
			this->pn_register->ResumeLayout(false);
			this->pn_register->PerformLayout();
			this->pn_start->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->welcomeScreen))->EndInit();
			this->pn_thankyou->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->thankyou))->EndInit();
			this->pn_defualt->ResumeLayout(false);
			this->pn_blank->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_blankpicutre))->EndInit();
			this->pn_products->ResumeLayout(false);
			this->panel11->ResumeLayout(false);
			this->flowLayoutPanel2->ResumeLayout(false);
			this->pn_edit_information->ResumeLayout(false);
			this->pn_orders->ResumeLayout(false);
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_picture->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->EndInit();
			this->pn_login->ResumeLayout(false);
			this->pn_login->PerformLayout();
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
private: System::Void lb_profile_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label6_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void welcomeScreen_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void btn_minimize_MouseHover(System::Object^ sender, System::EventArgs^ e) {
}

private: System::Void btn_register_registerpanel_Click(System::Object^ sender, System::EventArgs^ e) {
	
	//check  password
	String^ password = tb_password_register->Text;
	if (password->Length != 8 || !System::Text::RegularExpressions::Regex::IsMatch(password, "^[0-9]{8}$")) {
		lb_password_message->Text=("Password must be exactly 8 digits.");
		return;
	}
	else { lb_password_message->Text = (""); }

	//check  phone number
	String^ phone = tb_phonenumber_register->Text;
	if (phone->Length != 11 || !System::Text::RegularExpressions::Regex::IsMatch(phone, "^[0-9]{11}$")) {
		lb_phonenumber_message->Text = ("Phone number must be exactly 11 digits.");
		return;
	}
	else { lb_phonenumber_message->Text = (""); }
	

	//check username
	String^ username = tb_username_register->Text;
	if (File::Exists("customers.txt")) {
		for each (String ^ line in File::ReadAllLines("customers.txt")) {
			if (line->StartsWith(username + ",")) {
				lb_username_message->Text = ("Username already exists.");
				return;
			}
		}
	}
	else {
		lb_username_message->Text = ("");
	}
	try {
		StreamWriter^ sw = gcnew StreamWriter("customers.txt", true);
		String^ customer = tb_username_register->Text + "," + tb_password_register->Text + "," + tb_phonenumber_register->Text + "," + tb_location_register->Text;
		sw->WriteLine(customer);
		sw->Close();
		pn_login->BringToFront();
		for each (Control ^ c in this->Controls)
		{
			if (dynamic_cast<TextBox^>(c))
			{
				c->Text = "";
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
	pn_login->BringToFront();	
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
};
}
