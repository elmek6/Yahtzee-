#pragma once

namespace Yahtzee {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}
   		const static int _birler =0;
  		const static int _ikiler =1;
  		const static int _ucler  =2;
  		const static int _dortler=3;
  		const static int _besler =4;
  		const static int _altilar=5;
  		const static int _araTop =6;
  		const static int _bonus  =7;
  		const static int _3Turdes=8;
  		const static int _4Turdes=9;
  		const static int _doluEv =10;
  		const static int _darS   =11;
  		const static int _genisS =12;
  		const static int _yahtzee=13;
  		const static int _sans   =14;
  		const static int _toplam =15;

		
		bool static ZarAt;
    	int static zarAnim;
    	static array<int>^ zarlar = {1,1,1,1,1};
    	int static iZarSay;
    	//int OyuncuSay;
   		int static Siradaki;
	private: System::Windows::Forms::Label^  lblZar1;
	public: 
		static array<int,2>^Tablo = 
		{
		    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},
		    {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1}
		};

		///
		///
		///
		void ButonlarDiz(){
			Siradaki = 1;

			btn1->Enabled =  Tablo[Siradaki, _birler] == -1 ? true : false;
			btn2->Enabled =  Tablo[Siradaki, _ikiler] == -1 ? true : false;
			btn3->Enabled =  Tablo[Siradaki, _ucler] == -1 ? true : false;
			btn4->Enabled =  Tablo[Siradaki, _dortler] == -1 ? true : false;
			btn5->Enabled =  Tablo[Siradaki, _besler] == -1 ? true : false;
			btn6->Enabled =  Tablo[Siradaki, _altilar] == -1 ? true : false;

			
			btn3turdes->Enabled =  Tablo[Siradaki, _3Turdes] == -1 ? true : false;
			btn4turdes->Enabled =  Tablo[Siradaki, _4Turdes] == -1 ? true : false;
			btnDoluEv->Enabled =  Tablo[Siradaki, _doluEv] == -1 ? true : false;
			btnDarSokak->Enabled =  Tablo[Siradaki, _darS] == -1 ? true : false;
			btnGenisSokak->Enabled =  Tablo[Siradaki, _genisS] == -1 ? true : false;
			btnYahtzee->Enabled =  Tablo[Siradaki, _yahtzee] == -1 ? true : false;
			btnSans->Enabled =  Tablo[Siradaki, _sans] == -1 ? true : false;
		}


		///
		///
		///
		int TurdesSay(int hane){
			int sonuc = 0;
			int say = 0;

			for (int z = 1; z <= 6; z++) {
				say = 0;

				for (int i = 0; i <= 4; i++){
					if (zarlar[i] == z)	{
						say++;
					}
				}

				if (say >= hane) {
					sonuc = say;
				}
			}
			return say;
		}




		///
		///
		///
		int ZarlarToplam(){
			int t = 0;
			for (int i = 0; i <= 4; i++)
			{
				t = t + zarlar[i];
			}
			return t;
		}




		///
		///
		///
		int EnCokBitisik(){
			int say = 0;
			int sonuc = 0;
			char s[6+1] = "------";

			for (int i = 0; i <= 4; i++)
			{
				s[zarlar[i]-1] = '+';
			}


			/*
 		     *      -++++-
    	     *      --++++
    	     *      ++++-+
    	     *      +-++++
    	     */
        
		  	//en cok bitisik zarlar toplami=resume
			for (int i = 0; i <= 5; i++)
			{
				if (s[i] == '+')
				{
					say++;
				}
				else
				{
					say = 0;
				}

				if (say > sonuc)
				{
					sonuc = say;
				}
			}

			return sonuc;
		}


		
		///
		///
		///
		int DoluEv(){
			int aSay = 1;
			int aDeg = zarlar[0];
			int bSay = 0;
			int bDeg = 0;
			int sonuc = 0;


			for (int i = 1; i <= 4; i++)
			{
				if (bSay == 0 && aDeg != zarlar[i])
				{
					bDeg = zarlar[i];
				}

				if (zarlar[i] == aDeg)
				{
					aSay++;
				}

				if (zarlar[i] == bDeg)
				{
					bSay++;
				}

			}


			//iki turun toplamlari 5 ve farklari 3 degilse (4 1 gibi)
			if (aSay + bSay == 5 && Math::Abs(aSay-bSay) != 3)
			{
					sonuc = 25;
			}

			return sonuc;
		}



		///
		///
		///
		int RakamTop(int hane){
			int sonuc = 0;
			for (int i = 0; i <= 4; i++)
			{
				if (zarlar[i] == hane)
				{
					sonuc = sonuc + hane;
				}
			}
			return sonuc;
		}



		///
		///
		///
		void Yazdirilabilirler(){			
			if (!chkAcemiyim->Checked)
			{
				return;
			}

			lbl1->Text = RakamTop(1).ToString();
			lbl2->Text = RakamTop(2).ToString();
			lbl3->Text = RakamTop(3).ToString();
			lbl4->Text = RakamTop(4).ToString();
			lbl5->Text = RakamTop(5).ToString();
			lbl6->Text = RakamTop(6).ToString();

			if (TurdesSay(3) >= 3)
			{
				lbl3Turdes->Text = ZarlarToplam().ToString();
			}
			else
			{
				lbl3Turdes->Text = "0";
			}

            if (TurdesSay(4) >= 4) {
				lbl4Turdes->Text = ZarlarToplam().ToString();
			} else {
				lbl4Turdes->Text = "0";
			}

			lblDoluEv->Text = DoluEv().ToString();

			if (EnCokBitisik() >= 4)
			{
				lblDarSokak->Text = "30";
			}
			else
			{
				lblDarSokak->Text = "0";
			}
			

			if (EnCokBitisik()>=5)
			{
				lblGenisSokak->Text = "40";
			}
			else
			{
				lblGenisSokak->Text = "0";
			}			
			
			if (TurdesSay(5) >= 5)
			{
				lblYahtzee->Text = "50";
			}
			else
			{
				lblYahtzee->Text = "0";
			}
			
			lblSans->Text = ZarlarToplam().ToString();

		}



		///
		///
		///
		void TabloYaz(){
			int c = 1;
			int araTop = 0;
			int toplam = 0;

			for (int r = 0; r <= 14; r++)
			{
				if (r <= 5  &&  Tablo[c,r] != -1)
				{
					araTop = araTop + Tablo[c,r];

					if (araTop >= 63 )
					{
						Tablo[c, _bonus] = 35;
					}
				}


				if (Tablo[c, r] !=- 1)
				{
					toplam = toplam + Tablo[c, r];
				}


				if (Tablo[c, r ]== -1)
				{
					lstYazBoz->Items[r] = "";	     //   sgMain.Cells[c-1, r-1]:=''
				}
				else
				{
					lstYazBoz->Items[r] = Tablo[c, r].ToString();// sgMain.Cells[c-1, r-1]:=inttostr(Tablo[c][r]);
				}
			}

			lstYazBoz->Items[_araTop] = araTop.ToString();
			lstYazBoz->Items[_toplam] = toplam.ToString();
		}



		///
		///
		///



	private: System::Windows::Forms::ListBox^  listBox1;

	public: 

	    static array<int>^ a = { 5, 4, 1, 3, 2 };
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	public: 
	private: System::Windows::Forms::Label^  lbl2;
	private: System::Windows::Forms::Label^  lbl3;
	private: System::Windows::Forms::Label^  lbl4;
	private: System::Windows::Forms::Label^  lbl5;
	private: System::Windows::Forms::Label^  lbl6;
	private: System::Windows::Forms::Button^  btn1;
	private: System::Windows::Forms::Button^  btn2;
	private: System::Windows::Forms::Button^  btn3;
	private: System::Windows::Forms::Button^  btn4;
	private: System::Windows::Forms::Button^  btn5;
	private: System::Windows::Forms::Button^  btn6;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Button^  btn3turdes;
	private: System::Windows::Forms::Button^  btn4turdes;
	private: System::Windows::Forms::Button^  btnDoluEv;
	private: System::Windows::Forms::Button^  btnDarSokak;
	private: System::Windows::Forms::Button^  btnGenisSokak;
	private: System::Windows::Forms::Button^  btnYahtzee;
	private: System::Windows::Forms::Button^  btnSans;
	private: System::Windows::Forms::Label^  lbl3Turdes;
	private: System::Windows::Forms::Label^  lbl4Turdes;
	private: System::Windows::Forms::Label^  lblDoluEv;
	private: System::Windows::Forms::Label^  lblDarSokak;
	private: System::Windows::Forms::Label^  lblGenisSokak;
	private: System::Windows::Forms::Label^  lblYahtzee;
	private: System::Windows::Forms::Label^  lblSans;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  lbl1;
	private: System::Windows::Forms::ListBox^  lstYazBoz;
	private: System::Windows::Forms::Label^  lblZarSay;
	private: System::Windows::Forms::CheckBox^  chkAcemiyim;
	private: System::Windows::Forms::Label^  lblZar5;
	private: System::Windows::Forms::Label^  lblKalsin5;
	private: System::Windows::Forms::Label^  lblZar4;
	private: System::Windows::Forms::Label^  lblKalsin4;
	private: System::Windows::Forms::Label^  lblZar3;
	private: System::Windows::Forms::Label^  lblKalsin3;
	private: System::Windows::Forms::Label^  lblZar2;
	private: System::Windows::Forms::Label^  lblKalsin2;

	private: System::Windows::Forms::Label^  lblKalsin1;
	private: System::Windows::Forms::Button^  btnSalla;
	private: System::Windows::Forms::ImageList^  imageList1;
	private: System::Windows::Forms::Timer^  tmrZarlar;
			 static array<int>^ b;





	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::ComponentModel::IContainer^  components;
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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->lbl2 = (gcnew System::Windows::Forms::Label());
			this->lbl3 = (gcnew System::Windows::Forms::Label());
			this->lbl4 = (gcnew System::Windows::Forms::Label());
			this->lbl5 = (gcnew System::Windows::Forms::Label());
			this->lbl6 = (gcnew System::Windows::Forms::Label());
			this->btn1 = (gcnew System::Windows::Forms::Button());
			this->btn2 = (gcnew System::Windows::Forms::Button());
			this->btn3 = (gcnew System::Windows::Forms::Button());
			this->btn4 = (gcnew System::Windows::Forms::Button());
			this->btn5 = (gcnew System::Windows::Forms::Button());
			this->btn6 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->btn3turdes = (gcnew System::Windows::Forms::Button());
			this->btn4turdes = (gcnew System::Windows::Forms::Button());
			this->btnDoluEv = (gcnew System::Windows::Forms::Button());
			this->btnDarSokak = (gcnew System::Windows::Forms::Button());
			this->btnGenisSokak = (gcnew System::Windows::Forms::Button());
			this->btnYahtzee = (gcnew System::Windows::Forms::Button());
			this->btnSans = (gcnew System::Windows::Forms::Button());
			this->lbl3Turdes = (gcnew System::Windows::Forms::Label());
			this->lbl4Turdes = (gcnew System::Windows::Forms::Label());
			this->lblDoluEv = (gcnew System::Windows::Forms::Label());
			this->lblDarSokak = (gcnew System::Windows::Forms::Label());
			this->lblGenisSokak = (gcnew System::Windows::Forms::Label());
			this->lblYahtzee = (gcnew System::Windows::Forms::Label());
			this->lblSans = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lbl1 = (gcnew System::Windows::Forms::Label());
			this->lstYazBoz = (gcnew System::Windows::Forms::ListBox());
			this->lblZarSay = (gcnew System::Windows::Forms::Label());
			this->chkAcemiyim = (gcnew System::Windows::Forms::CheckBox());
			this->lblZar5 = (gcnew System::Windows::Forms::Label());
			this->lblKalsin5 = (gcnew System::Windows::Forms::Label());
			this->lblZar4 = (gcnew System::Windows::Forms::Label());
			this->lblKalsin4 = (gcnew System::Windows::Forms::Label());
			this->lblZar3 = (gcnew System::Windows::Forms::Label());
			this->lblKalsin3 = (gcnew System::Windows::Forms::Label());
			this->lblZar2 = (gcnew System::Windows::Forms::Label());
			this->lblKalsin2 = (gcnew System::Windows::Forms::Label());
			this->lblKalsin1 = (gcnew System::Windows::Forms::Label());
			this->btnSalla = (gcnew System::Windows::Forms::Button());
			this->imageList1 = (gcnew System::Windows::Forms::ImageList(this->components));
			this->tmrZarlar = (gcnew System::Windows::Forms::Timer(this->components));
			this->lblZar1 = (gcnew System::Windows::Forms::Label());
			this->tableLayoutPanel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(32, 348);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(162, 239);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(209, 264);
			this->listBox1->TabIndex = 3;
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 
				100)));
			this->tableLayoutPanel1->Controls->Add(this->lbl2, 0, 1);
			this->tableLayoutPanel1->Controls->Add(this->lbl3, 0, 2);
			this->tableLayoutPanel1->Controls->Add(this->lbl4, 0, 3);
			this->tableLayoutPanel1->Controls->Add(this->lbl5, 0, 4);
			this->tableLayoutPanel1->Controls->Add(this->lbl6, 0, 5);
			this->tableLayoutPanel1->Controls->Add(this->btn1, 1, 0);
			this->tableLayoutPanel1->Controls->Add(this->btn2, 1, 1);
			this->tableLayoutPanel1->Controls->Add(this->btn3, 1, 2);
			this->tableLayoutPanel1->Controls->Add(this->btn4, 1, 3);
			this->tableLayoutPanel1->Controls->Add(this->btn5, 1, 4);
			this->tableLayoutPanel1->Controls->Add(this->btn6, 1, 5);
			this->tableLayoutPanel1->Controls->Add(this->label1, 1, 6);
			this->tableLayoutPanel1->Controls->Add(this->label2, 1, 7);
			this->tableLayoutPanel1->Controls->Add(this->btn3turdes, 1, 8);
			this->tableLayoutPanel1->Controls->Add(this->btn4turdes, 1, 9);
			this->tableLayoutPanel1->Controls->Add(this->btnDoluEv, 1, 10);
			this->tableLayoutPanel1->Controls->Add(this->btnDarSokak, 1, 11);
			this->tableLayoutPanel1->Controls->Add(this->btnGenisSokak, 1, 12);
			this->tableLayoutPanel1->Controls->Add(this->btnYahtzee, 1, 13);
			this->tableLayoutPanel1->Controls->Add(this->btnSans, 1, 14);
			this->tableLayoutPanel1->Controls->Add(this->lbl3Turdes, 0, 8);
			this->tableLayoutPanel1->Controls->Add(this->lbl4Turdes, 0, 9);
			this->tableLayoutPanel1->Controls->Add(this->lblDoluEv, 0, 10);
			this->tableLayoutPanel1->Controls->Add(this->lblDarSokak, 0, 11);
			this->tableLayoutPanel1->Controls->Add(this->lblGenisSokak, 0, 12);
			this->tableLayoutPanel1->Controls->Add(this->lblYahtzee, 0, 13);
			this->tableLayoutPanel1->Controls->Add(this->lblSans, 0, 14);
			this->tableLayoutPanel1->Controls->Add(this->label3, 1, 15);
			this->tableLayoutPanel1->Controls->Add(this->lbl1, 0, 0);
			this->tableLayoutPanel1->Location = System::Drawing::Point(410, 65);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 16;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 29)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(123, 468);
			this->tableLayoutPanel1->TabIndex = 50;
			// 
			// lbl2
			// 
			this->lbl2->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl2->Location = System::Drawing::Point(3, 29);
			this->lbl2->Name = L"lbl2";
			this->lbl2->Size = System::Drawing::Size(31, 29);
			this->lbl2->TabIndex = 33;
			this->lbl2->Text = L"0";
			this->lbl2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl3
			// 
			this->lbl3->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl3->Location = System::Drawing::Point(3, 58);
			this->lbl3->Name = L"lbl3";
			this->lbl3->Size = System::Drawing::Size(31, 29);
			this->lbl3->TabIndex = 34;
			this->lbl3->Text = L"0";
			this->lbl3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl4
			// 
			this->lbl4->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl4->Location = System::Drawing::Point(3, 87);
			this->lbl4->Name = L"lbl4";
			this->lbl4->Size = System::Drawing::Size(31, 29);
			this->lbl4->TabIndex = 35;
			this->lbl4->Text = L"0";
			this->lbl4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl5
			// 
			this->lbl5->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl5->Location = System::Drawing::Point(3, 116);
			this->lbl5->Name = L"lbl5";
			this->lbl5->Size = System::Drawing::Size(31, 29);
			this->lbl5->TabIndex = 36;
			this->lbl5->Text = L"0";
			this->lbl5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl6
			// 
			this->lbl6->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl6->Location = System::Drawing::Point(3, 145);
			this->lbl6->Name = L"lbl6";
			this->lbl6->Size = System::Drawing::Size(31, 29);
			this->lbl6->TabIndex = 37;
			this->lbl6->Text = L"0";
			this->lbl6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btn1
			// 
			this->btn1->Location = System::Drawing::Point(40, 3);
			this->btn1->Name = L"btn1";
			this->btn1->Size = System::Drawing::Size(75, 23);
			this->btn1->TabIndex = 38;
			this->btn1->Text = L"Birler";
			this->btn1->UseVisualStyleBackColor = true;
			this->btn1->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn2
			// 
			this->btn2->Location = System::Drawing::Point(40, 32);
			this->btn2->Name = L"btn2";
			this->btn2->Size = System::Drawing::Size(75, 23);
			this->btn2->TabIndex = 39;
			this->btn2->Text = L"İkiler";
			this->btn2->UseVisualStyleBackColor = true;
			this->btn2->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn3
			// 
			this->btn3->Location = System::Drawing::Point(40, 61);
			this->btn3->Name = L"btn3";
			this->btn3->Size = System::Drawing::Size(75, 23);
			this->btn3->TabIndex = 40;
			this->btn3->Text = L"Üçler";
			this->btn3->UseVisualStyleBackColor = true;
			this->btn3->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn4
			// 
			this->btn4->Location = System::Drawing::Point(40, 90);
			this->btn4->Name = L"btn4";
			this->btn4->Size = System::Drawing::Size(75, 23);
			this->btn4->TabIndex = 41;
			this->btn4->Text = L"Dörtler";
			this->btn4->UseVisualStyleBackColor = true;
			this->btn4->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn5
			// 
			this->btn5->Location = System::Drawing::Point(40, 119);
			this->btn5->Name = L"btn5";
			this->btn5->Size = System::Drawing::Size(75, 23);
			this->btn5->TabIndex = 42;
			this->btn5->Text = L"Beşler";
			this->btn5->UseVisualStyleBackColor = true;
			this->btn5->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn6
			// 
			this->btn6->Location = System::Drawing::Point(40, 148);
			this->btn6->Name = L"btn6";
			this->btn6->Size = System::Drawing::Size(75, 23);
			this->btn6->TabIndex = 43;
			this->btn6->Text = L"Altılar";
			this->btn6->UseVisualStyleBackColor = true;
			this->btn6->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// label1
			// 
			this->label1->Location = System::Drawing::Point(40, 174);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(75, 23);
			this->label1->TabIndex = 45;
			this->label1->Text = L"Ara toplam";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Location = System::Drawing::Point(40, 203);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(75, 23);
			this->label2->TabIndex = 46;
			this->label2->Text = L"Bonus";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// btn3turdes
			// 
			this->btn3turdes->Location = System::Drawing::Point(40, 235);
			this->btn3turdes->Name = L"btn3turdes";
			this->btn3turdes->Size = System::Drawing::Size(75, 23);
			this->btn3turdes->TabIndex = 47;
			this->btn3turdes->Text = L"Üç türdeş";
			this->btn3turdes->UseVisualStyleBackColor = true;
			this->btn3turdes->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btn4turdes
			// 
			this->btn4turdes->Location = System::Drawing::Point(40, 264);
			this->btn4turdes->Name = L"btn4turdes";
			this->btn4turdes->Size = System::Drawing::Size(75, 23);
			this->btn4turdes->TabIndex = 48;
			this->btn4turdes->Text = L"Dört türdeş";
			this->btn4turdes->UseVisualStyleBackColor = true;
			this->btn4turdes->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btnDoluEv
			// 
			this->btnDoluEv->Location = System::Drawing::Point(40, 293);
			this->btnDoluEv->Name = L"btnDoluEv";
			this->btnDoluEv->Size = System::Drawing::Size(75, 23);
			this->btnDoluEv->TabIndex = 49;
			this->btnDoluEv->Text = L"Dolu ev";
			this->btnDoluEv->UseVisualStyleBackColor = true;
			this->btnDoluEv->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btnDarSokak
			// 
			this->btnDarSokak->Location = System::Drawing::Point(40, 322);
			this->btnDarSokak->Name = L"btnDarSokak";
			this->btnDarSokak->Size = System::Drawing::Size(75, 23);
			this->btnDarSokak->TabIndex = 50;
			this->btnDarSokak->Text = L"Dar sokak";
			this->btnDarSokak->UseVisualStyleBackColor = true;
			this->btnDarSokak->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btnGenisSokak
			// 
			this->btnGenisSokak->Location = System::Drawing::Point(40, 351);
			this->btnGenisSokak->Name = L"btnGenisSokak";
			this->btnGenisSokak->Size = System::Drawing::Size(75, 23);
			this->btnGenisSokak->TabIndex = 51;
			this->btnGenisSokak->Text = L"Geniş sokak";
			this->btnGenisSokak->UseVisualStyleBackColor = true;
			this->btnGenisSokak->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btnYahtzee
			// 
			this->btnYahtzee->Location = System::Drawing::Point(40, 380);
			this->btnYahtzee->Name = L"btnYahtzee";
			this->btnYahtzee->Size = System::Drawing::Size(75, 23);
			this->btnYahtzee->TabIndex = 52;
			this->btnYahtzee->Text = L"Yahtzee";
			this->btnYahtzee->UseVisualStyleBackColor = true;
			this->btnYahtzee->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// btnSans
			// 
			this->btnSans->Location = System::Drawing::Point(40, 409);
			this->btnSans->Name = L"btnSans";
			this->btnSans->Size = System::Drawing::Size(75, 23);
			this->btnSans->TabIndex = 53;
			this->btnSans->Text = L"Şans";
			this->btnSans->UseVisualStyleBackColor = true;
			this->btnSans->Click += gcnew System::EventHandler(this, &MainForm::btnTuslar);
			// 
			// lbl3Turdes
			// 
			this->lbl3Turdes->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl3Turdes->Location = System::Drawing::Point(3, 232);
			this->lbl3Turdes->Name = L"lbl3Turdes";
			this->lbl3Turdes->Size = System::Drawing::Size(31, 29);
			this->lbl3Turdes->TabIndex = 54;
			this->lbl3Turdes->Text = L"0";
			this->lbl3Turdes->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl4Turdes
			// 
			this->lbl4Turdes->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl4Turdes->Location = System::Drawing::Point(3, 261);
			this->lbl4Turdes->Name = L"lbl4Turdes";
			this->lbl4Turdes->Size = System::Drawing::Size(31, 29);
			this->lbl4Turdes->TabIndex = 55;
			this->lbl4Turdes->Text = L"0";
			this->lbl4Turdes->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblDoluEv
			// 
			this->lblDoluEv->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblDoluEv->Location = System::Drawing::Point(3, 290);
			this->lblDoluEv->Name = L"lblDoluEv";
			this->lblDoluEv->Size = System::Drawing::Size(31, 29);
			this->lblDoluEv->TabIndex = 56;
			this->lblDoluEv->Text = L"0";
			this->lblDoluEv->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblDarSokak
			// 
			this->lblDarSokak->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblDarSokak->Location = System::Drawing::Point(3, 319);
			this->lblDarSokak->Name = L"lblDarSokak";
			this->lblDarSokak->Size = System::Drawing::Size(31, 29);
			this->lblDarSokak->TabIndex = 57;
			this->lblDarSokak->Text = L"0";
			this->lblDarSokak->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblGenisSokak
			// 
			this->lblGenisSokak->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblGenisSokak->Location = System::Drawing::Point(3, 348);
			this->lblGenisSokak->Name = L"lblGenisSokak";
			this->lblGenisSokak->Size = System::Drawing::Size(31, 29);
			this->lblGenisSokak->TabIndex = 58;
			this->lblGenisSokak->Text = L"0";
			this->lblGenisSokak->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblYahtzee
			// 
			this->lblYahtzee->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblYahtzee->Location = System::Drawing::Point(3, 377);
			this->lblYahtzee->Name = L"lblYahtzee";
			this->lblYahtzee->Size = System::Drawing::Size(31, 29);
			this->lblYahtzee->TabIndex = 59;
			this->lblYahtzee->Text = L"0";
			this->lblYahtzee->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lblSans
			// 
			this->lblSans->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lblSans->Location = System::Drawing::Point(3, 406);
			this->lblSans->Name = L"lblSans";
			this->lblSans->Size = System::Drawing::Size(31, 29);
			this->lblSans->TabIndex = 60;
			this->lblSans->Text = L"0";
			this->lblSans->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label3
			// 
			this->label3->Location = System::Drawing::Point(40, 435);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(75, 23);
			this->label3->TabIndex = 61;
			this->label3->Text = L"Toplam";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lbl1
			// 
			this->lbl1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->lbl1->Location = System::Drawing::Point(3, 0);
			this->lbl1->Name = L"lbl1";
			this->lbl1->Size = System::Drawing::Size(31, 29);
			this->lbl1->TabIndex = 32;
			this->lbl1->Text = L"0";
			this->lbl1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// lstYazBoz
			// 
			this->lstYazBoz->BackColor = System::Drawing::SystemColors::Control;
			this->lstYazBoz->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->lstYazBoz->DisplayMember = L"2";
			this->lstYazBoz->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->lstYazBoz->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lstYazBoz->FormattingEnabled = true;
			this->lstYazBoz->ItemHeight = 29;
			this->lstYazBoz->Items->AddRange(gcnew cli::array< System::Object^  >(16) {L"", L"", L"", L"", L"", L"", L"", L"", L"", L"", 
				L"", L"", L"", L"", L"", L"0"});
			this->lstYazBoz->Location = System::Drawing::Point(539, 65);
			this->lstYazBoz->Name = L"lstYazBoz";
			this->lstYazBoz->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->lstYazBoz->SelectionMode = System::Windows::Forms::SelectionMode::None;
			this->lstYazBoz->Size = System::Drawing::Size(49, 464);
			this->lstYazBoz->TabIndex = 49;
			this->lstYazBoz->ValueMember = L"2";
			// 
			// lblZarSay
			// 
			this->lblZarSay->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblZarSay->Location = System::Drawing::Point(32, 39);
			this->lblZarSay->Name = L"lblZarSay";
			this->lblZarSay->Size = System::Drawing::Size(100, 23);
			this->lblZarSay->TabIndex = 63;
			this->lblZarSay->Text = L"0";
			this->lblZarSay->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// chkAcemiyim
			// 
			this->chkAcemiyim->Location = System::Drawing::Point(193, 39);
			this->chkAcemiyim->Name = L"chkAcemiyim";
			this->chkAcemiyim->Size = System::Drawing::Size(104, 23);
			this->chkAcemiyim->TabIndex = 62;
			this->chkAcemiyim->Text = L"Acemiyim";
			this->chkAcemiyim->UseVisualStyleBackColor = true;
			this->chkAcemiyim->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chkAcemiyim_CheckedChanged);
			// 
			// lblZar5
			// 
			this->lblZar5->ImageIndex = 6;
			this->lblZar5->ImageList = this->imageList1;
			this->lblZar5->Location = System::Drawing::Point(247, 70);
			this->lblZar5->Name = L"lblZar5";
			this->lblZar5->Size = System::Drawing::Size(48, 48);
			this->lblZar5->TabIndex = 61;
			this->lblZar5->Click += gcnew System::EventHandler(this, &MainForm::lblZarClick);
			// 
			// lblKalsin5
			// 
			this->lblKalsin5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblKalsin5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblKalsin5->Location = System::Drawing::Point(247, 130);
			this->lblKalsin5->Name = L"lblKalsin5";
			this->lblKalsin5->Size = System::Drawing::Size(48, 20);
			this->lblKalsin5->TabIndex = 60;
			this->lblKalsin5->Text = L"KALSIN";
			this->lblKalsin5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKalsin5->Visible = false;
			// 
			// lblZar4
			// 
			this->lblZar4->ImageIndex = 6;
			this->lblZar4->ImageList = this->imageList1;
			this->lblZar4->Location = System::Drawing::Point(193, 70);
			this->lblZar4->Name = L"lblZar4";
			this->lblZar4->Size = System::Drawing::Size(48, 48);
			this->lblZar4->TabIndex = 59;
			this->lblZar4->Click += gcnew System::EventHandler(this, &MainForm::lblZarClick);
			// 
			// lblKalsin4
			// 
			this->lblKalsin4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblKalsin4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblKalsin4->Location = System::Drawing::Point(193, 130);
			this->lblKalsin4->Name = L"lblKalsin4";
			this->lblKalsin4->Size = System::Drawing::Size(48, 20);
			this->lblKalsin4->TabIndex = 58;
			this->lblKalsin4->Text = L"KALSIN";
			this->lblKalsin4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKalsin4->Visible = false;
			// 
			// lblZar3
			// 
			this->lblZar3->ImageIndex = 6;
			this->lblZar3->ImageList = this->imageList1;
			this->lblZar3->Location = System::Drawing::Point(139, 70);
			this->lblZar3->Name = L"lblZar3";
			this->lblZar3->Size = System::Drawing::Size(48, 48);
			this->lblZar3->TabIndex = 57;
			this->lblZar3->Click += gcnew System::EventHandler(this, &MainForm::lblZarClick);
			// 
			// lblKalsin3
			// 
			this->lblKalsin3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblKalsin3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblKalsin3->Location = System::Drawing::Point(139, 130);
			this->lblKalsin3->Name = L"lblKalsin3";
			this->lblKalsin3->Size = System::Drawing::Size(48, 20);
			this->lblKalsin3->TabIndex = 56;
			this->lblKalsin3->Text = L"KALSIN";
			this->lblKalsin3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKalsin3->Visible = false;
			// 
			// lblZar2
			// 
			this->lblZar2->ImageIndex = 6;
			this->lblZar2->ImageList = this->imageList1;
			this->lblZar2->Location = System::Drawing::Point(85, 70);
			this->lblZar2->Name = L"lblZar2";
			this->lblZar2->Size = System::Drawing::Size(48, 48);
			this->lblZar2->TabIndex = 55;
			this->lblZar2->Click += gcnew System::EventHandler(this, &MainForm::lblZarClick);
			// 
			// lblKalsin2
			// 
			this->lblKalsin2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblKalsin2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblKalsin2->Location = System::Drawing::Point(85, 130);
			this->lblKalsin2->Name = L"lblKalsin2";
			this->lblKalsin2->Size = System::Drawing::Size(48, 20);
			this->lblKalsin2->TabIndex = 54;
			this->lblKalsin2->Text = L"KALSIN";
			this->lblKalsin2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKalsin2->Visible = false;
			// 
			// lblKalsin1
			// 
			this->lblKalsin1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->lblKalsin1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lblKalsin1->Location = System::Drawing::Point(31, 130);
			this->lblKalsin1->Name = L"lblKalsin1";
			this->lblKalsin1->Size = System::Drawing::Size(48, 20);
			this->lblKalsin1->TabIndex = 52;
			this->lblKalsin1->Text = L"KALSIN";
			this->lblKalsin1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lblKalsin1->Visible = false;
			// 
			// btnSalla
			// 
			this->btnSalla->Location = System::Drawing::Point(32, 165);
			this->btnSalla->Name = L"btnSalla";
			this->btnSalla->Size = System::Drawing::Size(263, 42);
			this->btnSalla->TabIndex = 51;
			this->btnSalla->Text = L"Zarları salla";
			this->btnSalla->UseVisualStyleBackColor = true;
			this->btnSalla->Click += gcnew System::EventHandler(this, &MainForm::btnSalla_Click);
			// 
			// imageList1
			// 
			this->imageList1->ImageStream = (cli::safe_cast<System::Windows::Forms::ImageListStreamer^  >(resources->GetObject(L"imageList1.ImageStream")));
			this->imageList1->TransparentColor = System::Drawing::Color::Lime;
			this->imageList1->Images->SetKeyName(0, L"ZAR1.bmp");
			this->imageList1->Images->SetKeyName(1, L"ZAR2.bmp");
			this->imageList1->Images->SetKeyName(2, L"ZAR3.bmp");
			this->imageList1->Images->SetKeyName(3, L"ZAR4.bmp");
			this->imageList1->Images->SetKeyName(4, L"ZAR5.bmp");
			this->imageList1->Images->SetKeyName(5, L"ZAR6.bmp");
			this->imageList1->Images->SetKeyName(6, L"ZARa.bmp");
			this->imageList1->Images->SetKeyName(7, L"ZARk.bmp");
			// 
			// tmrZarlar
			// 
			this->tmrZarlar->Interval = 50;
			this->tmrZarlar->Tick += gcnew System::EventHandler(this, &MainForm::tmrZarlar_Tick);
			// 
			// lblZar1
			// 
			this->lblZar1->ImageIndex = 6;
			this->lblZar1->ImageList = this->imageList1;
			this->lblZar1->Location = System::Drawing::Point(31, 70);
			this->lblZar1->Name = L"lblZar1";
			this->lblZar1->Size = System::Drawing::Size(48, 48);
			this->lblZar1->TabIndex = 53;
			this->lblZar1->Click += gcnew System::EventHandler(this, &MainForm::lblZarClick);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(610, 547);
			this->Controls->Add(this->lblZarSay);
			this->Controls->Add(this->chkAcemiyim);
			this->Controls->Add(this->lblZar5);
			this->Controls->Add(this->lblKalsin5);
			this->Controls->Add(this->lblZar4);
			this->Controls->Add(this->lblKalsin4);
			this->Controls->Add(this->lblZar3);
			this->Controls->Add(this->lblKalsin3);
			this->Controls->Add(this->lblZar2);
			this->Controls->Add(this->lblKalsin2);
			this->Controls->Add(this->lblZar1);
			this->Controls->Add(this->lblKalsin1);
			this->Controls->Add(this->btnSalla);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->lstYazBoz);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->button1);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->tableLayoutPanel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

		Random^ randObj = gcnew Random(  );

		this->Text = randObj->Next(1, 6).ToString();

		Array::Sort( a );
		for (int i=0; i < a->Length; i++)
		{
		//listBox1->Items->Add(a[i]); 
			listBox1->Items->Add(randObj->Next(1, 6).ToString());
		}
	}

	private: System::Void btnSalla_Click(System::Object^  sender, System::EventArgs^  e) {
		iZarSay++;
		ZarAt = false; 

		lblZarSay->Text = iZarSay.ToString();
  			
		btnSalla->Enabled = false;
		tmrZarlar->Enabled = true; 	
	}



	private: System::Void tmrZarlar_Tick(System::Object^  sender, System::EventArgs^  e) {
		Random^ randObj = gcnew Random();

		if (!lblKalsin1->Visible) zarlar[0] = randObj->Next(1, 7);
		if (!lblKalsin2->Visible) zarlar[1] = randObj->Next(1, 7);
		if (!lblKalsin3->Visible) zarlar[2] = randObj->Next(1, 7);
		if (!lblKalsin4->Visible) zarlar[3] = randObj->Next(1, 7);
		if (!lblKalsin5->Visible) zarlar[4] = randObj->Next(1, 7);

		lblZar1->ImageIndex = zarlar[0]-1;
		lblZar2->ImageIndex = zarlar[1]-1;
		lblZar3->ImageIndex = zarlar[2]-1;
		lblZar4->ImageIndex = zarlar[3]-1;
		lblZar5->ImageIndex = zarlar[4]-1;
			 
		zarAnim++;
			
		if (zarAnim>10)
		{
		zarAnim = 0;
		tmrZarlar->Enabled = false;
				
		if (iZarSay < 3)
		{
			btnSalla->Enabled = true;
		}

		Yazdirilabilirler();
		}

	 }

	private: System::Void btnTuslar(System::Object^  sender, System::EventArgs^  e) {
			 
			if (ZarAt)
			{
				MessageBox::Show("El yazdirin, Zar atmanız gerekiyor");
				return;
			}


			ZarAt = true;
			Siradaki = 1;
			if (sender == btn1) Tablo[Siradaki, _birler] = RakamTop(1);
			if (sender == btn2) Tablo[Siradaki, _ikiler] = RakamTop(2);
			if (sender == btn3) Tablo[Siradaki, _ucler] = RakamTop(3);
			if (sender == btn4) Tablo[Siradaki, _dortler] = RakamTop(4);
			if (sender == btn5) Tablo[Siradaki, _besler] = RakamTop(5);
		 	if (sender == btn6) Tablo[Siradaki, _altilar] = RakamTop(6);


			//3 Turdes, Zarlarin toplami
			if (sender == btn3turdes) {
				if (TurdesSay(3) >= 3)
				{
					Tablo[Siradaki, _3Turdes] = ZarlarToplam();
				}
				else
				{
					Tablo[Siradaki, _3Turdes] = 0;
					
				}
			}


			//4 Turdes, Zarlarin toplami
			if (sender == btn4turdes) {
				if (TurdesSay(4) >= 4) {
					Tablo[Siradaki, _4Turdes] = ZarlarToplam();
				} else {
					Tablo[Siradaki, _4Turdes] = 0;
					
				}
			}

			
			//Dolu ev, 25 puan
			if (sender == btnDoluEv) {
				Tablo[Siradaki, _doluEv] = DoluEv();
			}

			
			//Dar sokak, 30 puan
			if (sender == btnDarSokak) {
				if (EnCokBitisik() >= 4) {
					Tablo[Siradaki, _darS] = 30;
				} else {
					Tablo[Siradaki, _darS] = 0;
				}
			}
			
			
			//Genis sokak, 40 puan
			if (sender == btnGenisSokak) {
				if (EnCokBitisik() == 5 ) {
					Tablo[Siradaki, _genisS] = 40;
				} else {
					Tablo[Siradaki, _genisS] = 0;
				}
			}
			
			
			//5 Turdes Yahtzee, 50 puan
			if (sender == btnYahtzee) {
				if (TurdesSay(5) >= 5) {
					Tablo[Siradaki, _yahtzee] = 50;
				} else {
					Tablo[Siradaki, _yahtzee] = 0;
				}
			}


			//Sans, Zarlarin Toplami
			if (sender == btnSans) {
				Tablo[Siradaki, _sans] = ZarlarToplam();
			}
			
			
			lblKalsin1->Visible = false;
			lblKalsin2->Visible = false;
			lblKalsin3->Visible = false;
			lblKalsin4->Visible = false;
			lblKalsin5->Visible = false;

			TabloYaz();
			/*
			if Siradaki>=OyuncuSay then
			Siradaki:=1
			else
			inc(Siradaki);
			*/
			ButonlarDiz();

			//  lblOyuncu1.Transparent := Siradaki<>1;
			//  lblOyuncu2.Transparent := Siradaki<>2;
			//  lblOyuncu3.Transparent := Siradaki<>3;

			iZarSay = 0;
			btnSalla->Enabled = true;
			lblZarSay->Text = "Tekrar zar atin";       

	}

	private: System::Void lblZarClick(System::Object^  sender, System::EventArgs^  e) {
		//ilk el zar tutma olmaz
		if (iZarSay == 0) {
			return;
		}
			
		  	
		if (sender == lblZar1) lblKalsin1->Visible = ! lblKalsin1->Visible;
		if (sender == lblZar2) lblKalsin2->Visible = ! lblKalsin2->Visible;
		if (sender == lblZar3) lblKalsin3->Visible = ! lblKalsin3->Visible;
		if (sender == lblZar4) lblKalsin4->Visible = ! lblKalsin4->Visible;
		if (sender == lblZar5) lblKalsin5->Visible = ! lblKalsin5->Visible;
	}


	private: System::Void chkAcemiyim_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
		if (chkAcemiyim->Checked) {
			Yazdirilabilirler();
		}

		lbl1->Visible = chkAcemiyim->Checked;
		lbl2->Visible = chkAcemiyim->Checked;
		lbl3->Visible = chkAcemiyim->Checked;
		lbl4->Visible = chkAcemiyim->Checked;
		lbl5->Visible = chkAcemiyim->Checked;
		lbl6->Visible = chkAcemiyim->Checked;

		lbl3Turdes->Visible    = chkAcemiyim->Checked;
		lbl4Turdes->Visible    = chkAcemiyim->Checked;
		lblDoluEv->Visible     = chkAcemiyim->Checked;
		lblDarSokak->Visible   = chkAcemiyim->Checked;
		lblGenisSokak->Visible = chkAcemiyim->Checked;
		lblYahtzee->Visible    = chkAcemiyim->Checked;
		lblSans->Visible       = chkAcemiyim->Checked;

	}
};
}
