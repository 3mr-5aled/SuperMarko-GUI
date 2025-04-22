#pragma once

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
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;









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
			this->pn_blank = (gcnew System::Windows::Forms::Panel());
			this->pn_orders = (gcnew System::Windows::Forms::Panel());
			this->pn_products = (gcnew System::Windows::Forms::Panel());
			this->pn_edit_information = (gcnew System::Windows::Forms::Panel());
			this->pn_left_bar = (gcnew System::Windows::Forms::Panel());
			this->flowLayoutPanel1 = (gcnew System::Windows::Forms::FlowLayoutPanel());
			this->btn_edit_information = (gcnew System::Windows::Forms::Button());
			this->btn_products = (gcnew System::Windows::Forms::Button());
			this->btn_orders = (gcnew System::Windows::Forms::Button());
			this->btn_login = (gcnew System::Windows::Forms::Button());
			this->pn_picture = (gcnew System::Windows::Forms::Panel());
			this->lb_profile = (gcnew System::Windows::Forms::Label());
			this->pb_profile = (gcnew System::Windows::Forms::PictureBox());
			this->pn_start = (gcnew System::Windows::Forms::Panel());
			this->pn_login = (gcnew System::Windows::Forms::Panel());
			this->pn_register = (gcnew System::Windows::Forms::Panel());
			this->pn_thankyou = (gcnew System::Windows::Forms::Panel());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->pn_upper_bar->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_icon))->BeginInit();
			this->pn_main_dashboard->SuspendLayout();
			this->pn_defualt->SuspendLayout();
			this->pn_blank->SuspendLayout();
			this->pn_orders->SuspendLayout();
			this->pn_products->SuspendLayout();
			this->pn_edit_information->SuspendLayout();
			this->pn_left_bar->SuspendLayout();
			this->flowLayoutPanel1->SuspendLayout();
			this->pn_picture->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->BeginInit();
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
			this->pn_main_dashboard->Controls->Add(this->pn_login);
			this->pn_main_dashboard->Controls->Add(this->pn_register);
			this->pn_main_dashboard->Controls->Add(this->pn_thankyou);
			this->pn_main_dashboard->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_main_dashboard->Location = System::Drawing::Point(0, 55);
			this->pn_main_dashboard->Name = L"pn_main_dashboard";
			this->pn_main_dashboard->Size = System::Drawing::Size(1500, 745);
			this->pn_main_dashboard->TabIndex = 1;
			// 
			// pn_defualt
			// 
			this->pn_defualt->Controls->Add(this->pn_blank);
			this->pn_defualt->Controls->Add(this->pn_products);
			this->pn_defualt->Controls->Add(this->pn_orders);
			this->pn_defualt->Controls->Add(this->pn_edit_information);
			this->pn_defualt->Controls->Add(this->pn_left_bar);
			this->pn_defualt->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_defualt->Location = System::Drawing::Point(0, 0);
			this->pn_defualt->Name = L"pn_defualt";
			this->pn_defualt->Size = System::Drawing::Size(1500, 745);
			this->pn_defualt->TabIndex = 4;
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
			// pn_orders
			// 
			this->pn_orders->Controls->Add(this->label2);
			this->pn_orders->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_orders->Location = System::Drawing::Point(296, 0);
			this->pn_orders->Name = L"pn_orders";
			this->pn_orders->Size = System::Drawing::Size(1204, 745);
			this->pn_orders->TabIndex = 3;
			// 
			// pn_products
			// 
			this->pn_products->Controls->Add(this->label3);
			this->pn_products->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_products->Location = System::Drawing::Point(296, 0);
			this->pn_products->Name = L"pn_products";
			this->pn_products->Size = System::Drawing::Size(1204, 745);
			this->pn_products->TabIndex = 2;
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
			// pn_start
			// 
			this->pn_start->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_start->Location = System::Drawing::Point(0, 0);
			this->pn_start->Name = L"pn_start";
			this->pn_start->Size = System::Drawing::Size(1500, 745);
			this->pn_start->TabIndex = 3;
			// 
			// pn_login
			// 
			this->pn_login->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_login->Location = System::Drawing::Point(0, 0);
			this->pn_login->Name = L"pn_login";
			this->pn_login->Size = System::Drawing::Size(1500, 745);
			this->pn_login->TabIndex = 2;
			// 
			// pn_register
			// 
			this->pn_register->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_register->Location = System::Drawing::Point(0, 0);
			this->pn_register->Name = L"pn_register";
			this->pn_register->Size = System::Drawing::Size(1500, 745);
			this->pn_register->TabIndex = 1;
			// 
			// pn_thankyou
			// 
			this->pn_thankyou->Dock = System::Windows::Forms::DockStyle::Fill;
			this->pn_thankyou->Location = System::Drawing::Point(0, 0);
			this->pn_thankyou->Name = L"pn_thankyou";
			this->pn_thankyou->Size = System::Drawing::Size(1500, 745);
			this->pn_thankyou->TabIndex = 0;
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
			// label3
			// 
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16.2F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(271, 297);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(663, 151);
			this->label3->TabIndex = 1;
			this->label3->Text = L"products";
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
			this->pn_blank->ResumeLayout(false);
			this->pn_orders->ResumeLayout(false);
			this->pn_products->ResumeLayout(false);
			this->pn_edit_information->ResumeLayout(false);
			this->pn_left_bar->ResumeLayout(false);
			this->flowLayoutPanel1->ResumeLayout(false);
			this->pn_picture->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_profile))->EndInit();
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
};
}
