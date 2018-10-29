
//This is code I wrote to actually make the histograms. It produces 9 canvases: phi, cos, and length of muon: x,y,z vertex of the interaction: PFP, shower, and track particle multiplicity. The canvases include 3 plots each: MC, data, and a comparision. That last one is currently commented out because I am not sure if I quite understand it and if it is working correctly.

{

  //These are the rootfiles that you created in your .C files
  TFile *f1=new TFile("mc_tag1_histos.root"); //MAKE SURE THESE ARE ALL TAG 0!!!!
  TFile *f2=new TFile("bnb_tag1_histos.root");
  TFile *f3=new TFile("ext_tag1_histos.root");
  
  // All the things for the muon candidate: anything with _1 is data and _2 is ext
  TH1D * h1 = (TH1D*)f1->Get("h_truth_phi_muon_mc");
  TH1D * h2 = (TH1D*)f1->Get("h_cos_truth_theta_muon_mc");
  TH1D * h3 = (TH1D*)f1->Get("h_muon_length_mc");
  
  TH1D * h1_1 = (TH1D*)f2->Get("h_truth_phi_muon_bnb");
  TH1D * h2_1 = (TH1D*)f2->Get("h_cos_truth_theta_muon_bnb");
  TH1D * h3_1 = (TH1D*)f2->Get("h_muon_length_bnb");

  TH1D * h1_2 = (TH1D*)f3->Get("h_truth_phi_muon_ext");
  TH1D * h2_2 = (TH1D*)f3->Get("h_cos_truth_theta_muon_ext");
  TH1D * h3_2 = (TH1D*)f3->Get("h_muon_length_ext");

  //All the things for the x,y,z coordinates of the vertex
  TH1D * h4 = (TH1D*)f1->Get("h_vertex_x_mc");
  TH1D * h5 = (TH1D*)f1->Get("h_vertex_y_mc");
  TH1D * h6 = (TH1D*)f1->Get("h_vertex_z_mc");
  
  TH1D * h4_1 = (TH1D*)f2->Get("h_vertex_x_bnb");
  TH1D * h5_1 = (TH1D*)f2->Get("h_vertex_y_bnb");
  TH1D * h6_1 = (TH1D*)f2->Get("h_vertex_z_bnb");

  TH1D * h4_2 = (TH1D*)f3->Get("h_vertex_x_ext");
  TH1D * h5_2 = (TH1D*)f3->Get("h_vertex_y_ext");
  TH1D * h6_2 = (TH1D*)f3->Get("h_vertex_z_ext");

  //All the things for the multiplicity
  TH1D * h7 = (TH1D*)f1->Get("h_shower_mc");
  TH1D * h8 = (TH1D*)f1->Get("h_pfp_mc");
  TH1D * h9 = (TH1D*)f1->Get("h_track_mc");
  
  TH1D * h7_1 = (TH1D*)f2->Get("h_shower_bnb");
  TH1D * h8_1 = (TH1D*)f2->Get("h_pfp_bnb");
  TH1D * h9_1 = (TH1D*)f2->Get("h_track_bnb");

  TH1D * h7_2 = (TH1D*)f3->Get("h_shower_ext");
  TH1D * h8_2 = (TH1D*)f3->Get("h_pfp_ext");
  TH1D * h9_2 = (TH1D*)f3->Get("h_track_ext");

  ///////////////////////////////////////////////////////
  //NOW HERE IS CANVAS 1
  /////////////////////////////////////////////////////
  TCanvas *c1= new TCanvas("c1","Phi of Muon",1500,1000);
  //c1->Divide(2,1);
;
  c1->cd(1);
  
  THStack *hs1 = new THStack("hs1","Phi of the Muon");
  TPad *pad1 = new TPad("pad1", "pad1", 0, 0.3, 1, 1.0);
  pad1->SetBottomMargin(0); // Upper and lower plot are joined
  pad1->SetGridx();
  pad1->Draw();             // Draw the upper pad: pad1
  pad1->cd();  
  hs1->SetTitle("Phi of Muon; Phi(radians);# of Events");
  hs1->Add(h1);
  hs1->Add(h1_2);  
  hs1->Draw("hist");
  h1->SetLineColor(kRed+2);
  h1->SetFillColor(kRed);
  h1->SetLineWidth(1);
  //h1->SetStats(kFALSE);
  h1_2->SetLineColor(kBlue+2);
  h1_2->SetLineWidth(1);
  h1_2->SetFillStyle(3005);
  h1_2->SetFillColor(kBlue);;
  hs1->GetYaxis()->SetTitleSize(20);
  hs1->GetYaxis()->SetTitleFont(43);
  hs1->GetYaxis()->SetTitleOffset(1.5);
  //hs1->SetMaximum(400);
  
  //h1_1->Add(h1_2,-1);
  h1_1->Draw("e1SAME");
  //h1_1->SetMarkerStyle(5);
  //h1->SetTitle("Phi of Muon; Phi(radians);# of Events");
  //h1_1->Draw("eSAME");
  h1_1->SetLineColor(kBlack);
  h1_1->SetLineWidth(2);
  //h1_1->SetStats(kFALSE);
  //h1_1>SetFillColor(kRed);

  auto legend_1 = new TLegend(0.8,0.8,0.9,0.9);
  legend_1->AddEntry(h1,"MC:Tag 1","pf");
  legend_1->AddEntry(h1_1,"BNB: Tag 1","lepf");
  legend_1->AddEntry(h1_2, "EXT: Tag 1","pf");
  legend_1->SetTextFont(42);
  legend_1->Draw();

  c1->cd();          // Go back to the main canvas before defining pad2
  
  TPad *pad2 = new TPad("pad2", "pad2", 0, 0.05, 1, 0.3);
  pad2->SetTopMargin(0);
  pad2->SetBottomMargin(0.2);
  pad2->SetGridx(); // vertical grid
  pad2->Draw();
  pad2->cd();       // pad2 becomes the current pad
  TH1F *h1_3 = (TH1F*)h1_1->Clone("h1_3");
  TH1F *h1_4 = (TH1F*)h1_2->Clone("h1_4");
  h1_4->Add(h1);
  h1_3->Divide(h1_3,h1_4,1,1,"B");
  h1_3->Draw("e1p");
  // h1_3->SetMinimum(-1);  // Define Y ..
  //h1_3->SetMaximum(4); // .. range
  h1_3->SetStats(kFALSE);
  h1_3->SetTitle("");

  TF1 *a1 = new TF1("a1","1", -3.15 , 3.2);
  a1->SetLineColor(kRed+2);
  a1->Draw("SAME");

     // Y axis ratio plot settings
   h1_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
   h1_3->GetYaxis()->SetNdivisions(505);
   h1_3->GetYaxis()->SetTitleSize(20);
   h1_3->GetYaxis()->SetTitleFont(43);
   h1_3->GetYaxis()->SetTitleOffset(1.5);
   h1_3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h1_3->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h1_3->GetXaxis()->SetTitle("Phi (Radians)");
   h1_3->GetXaxis()->SetTitleSize(20);
   h1_3->GetXaxis()->SetTitleFont(43);
   h1_3->GetXaxis()->SetTitleOffset(4);
   h1_3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h1_3->GetXaxis()->SetLabelSize(15);

   c1->Print("analysis1_1/MCC9_phi_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 2
  //////////////////////
  TCanvas *c2= new TCanvas("c2","Cos(theta) of the Muon",1500,1000);
  c2->cd(1);
  
  THStack *hs2 = new THStack("hs2","Cos(theta) of the Muon");
  TPad *pad3 = new TPad("pad3", "pad3", 0, 0.3, 1, 1.0);
  pad3->SetBottomMargin(0); // Upper and lower plot are joined
  pad3->SetGridx();
  pad3->Draw();             // Draw the upper pad: pad1
  pad3->cd();               // pad1 becomes the current pad
  hs2->SetTitle("Cos(theta) of the Muon; cos(theta);# of Events");
  hs2->Add(h2);
  hs2->Add(h2_2);
  hs2->Draw("hist");
  h2->SetLineColor(kRed+2);
  h2->SetFillColor(kRed);
  h2->SetLineWidth(1);
  h2_2->SetLineColor(kBlue+2);
  h2_2->SetLineWidth(1);
  h2_2->SetFillColor(kBlue);
  h2_2->SetFillStyle(3005);
  hs2->GetYaxis()->SetTitleSize(20);
  hs2->GetYaxis()->SetTitleFont(43);
  hs2->GetYaxis()->SetTitleOffset(1.5);
  hs2->SetMaximum(1700);
  
  //Draw the BNB on the same histogram as black points with errorbars
  h2_1->Draw("e1SAME");
  //h2->SetTitle("Cos(theta) of Muon; Phi(radians);# of Events");
  //h2_1->Draw("eSAME");
  h2_1->SetLineColor(kBlack);
  h2_1->SetLineWidth(2);
  //h2->SetStats(kFALSE);
  //h2->SetFillColor(kRed);

  auto legend_2 = new TLegend(0.8,0.8,0.9,0.9);
  legend_2->AddEntry(h2,"MC Tag 1","pf");
  legend_2->AddEntry(h2_1,"BNB Tag 1","lepf");
  legend_2->AddEntry(h2_2, "EXT Tag 1","pf");
  legend_2->SetTextFont(42);
  legend_2->Draw();

    // lower plot will be in pad
  c2->cd();          // Go back to the main canvas before defining pad2
  TPad *pad4 = new TPad("pad4", "pad4", 0, 0.05, 1, 0.3);
  pad4->SetTopMargin(0);
  pad4->SetBottomMargin(0.2);
  pad4->SetGridx(); // vertical grid
  pad4->Draw();
  pad4->cd();       // pad2 becomes the current pad
  TH1F *h2_3 = (TH1F*)h2_1->Clone("h2_3");
  TH1F *h2_4 = (TH1F*)h2_2->Clone("h2_4");
  h2_4->Add(h2);
  h2_3->Divide(h2_3,h2_4,1,1,"B");
  h2_3->Draw("e1p");
  //h2_3->SetMinimum(0);  // Define Y ..
  //h2_3->SetMaximum(1.8); // .. range
  h2_3->SetStats(kFALSE);
  h2_3->SetTitle("");

  TF1 *a2 = new TF1("a2","1", -1 , 1);
  a2->SetLineColor(kRed+2);
  a2->Draw("SAME");

     // Y axis ratio plot settings
   h2_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
   h2_3->GetYaxis()->SetNdivisions(505);
   h2_3->GetYaxis()->SetTitleSize(20);
   h2_3->GetYaxis()->SetTitleFont(43);
   h2_3->GetYaxis()->SetTitleOffset(1.5);
   h2_3->GetYaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h2_3->GetYaxis()->SetLabelSize(15);

   // X axis ratio plot settings
   h2_3->GetXaxis()->SetTitle("cos(theta)");
   h2_3->GetXaxis()->SetTitleSize(20);
   h2_3->GetXaxis()->SetTitleFont(43);
   h2_3->GetXaxis()->SetTitleOffset(4);
   h2_3->GetXaxis()->SetLabelFont(43); // Absolute font size in pixel (precision 3)
   h2_3->GetXaxis()->SetLabelSize(15);

   c2->Print("analysis1_1/MCC9_costheta_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 3
  //////////////////////
  TCanvas *c3= new TCanvas("c3","Length of Muon",1500,1000);
  c3->cd(1);
  
  THStack *hs3 = new THStack("hs3","Length of Muon");
  TPad *pad5 = new TPad("pad5", "pad5", 0, 0.3, 1, 1.0);
  pad5->SetBottomMargin(0); 
  pad5->SetGridx();
  pad5->Draw();             
  pad5->cd(); 
  hs3->SetTitle("Length of the Muon; Length of Track (cm);# of Events");
  hs3->Add(h3);
  hs3->Add(h3_2);
  hs3->Draw("hist");
  h3->SetLineColor(kRed+2);
  h3->SetFillColor(kRed);
  h3->SetLineWidth(1);
  h3_2->SetLineColor(kBlue+2);
  h3_2->SetLineWidth(1);
  h3_2->SetFillColor(kBlue);
  h3_2->SetFillStyle(3005);
  hs3->GetYaxis()->SetTitleOffset(1.3);
  hs3->GetYaxis()->SetTitleSize(20);
  hs3->GetYaxis()->SetTitleFont(43);
  hs3->GetYaxis()->SetTitleOffset(1.5);
  hs3->SetMaximum(2500);
  
  h3_1->Draw("e1SAME");
  //h3_1->Draw("eSAME");
  //h3->SetTitle("Length of the Muon; Length of Track (cm);# of Events");
  h3_1->SetLineColor(kBlack);
  h3_1->SetLineWidth(2);
  //h3->SetStats(kFALSE);
  //h3->SetFillColor(kRed);

  auto legend_3 = new TLegend(0.8,0.8,0.9,0.9);
  legend_3->AddEntry(h3,"MC Tag 1","pf");
  legend_3->AddEntry(h3_1,"BNB Tag 1","lepf");
  legend_3->AddEntry(h3_2, "EXT Tag 1","pf");
  legend_3->SetTextFont(42);
  legend_3->Draw();
  
  c3->cd();      
  TPad *pad6 = new TPad("pad6", "pad6", 0, 0.05, 1, 0.3);
  pad6->SetTopMargin(0);
  pad6->SetBottomMargin(0.2);
  pad6->SetGridx(); 
  pad6->Draw();
  pad6->cd();       
  TH1F *h3_3 = (TH1F*)h3_1->Clone("h3_3");
  TH1F *h3_4 = (TH1F*)h3_2->Clone("h3_4");
  h3_4->Add(h3);
  h3_3->Divide(h3_3,h3_4,1,1,"B");
  h3_3->Draw("e1p");
  //h3_3->SetMinimum(0);  
  //h3_3->SetMaximum(3.5); 
  h3_3->SetStats(kFALSE);
  h3_3->SetTitle("");

  TF1 *a3 = new TF1("a3","1", 0 , 700);
  a3->SetLineColor(kRed+2);
  a3->Draw("SAME");

  // Y axis ratio plot settings
  h3_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h3_3->GetYaxis()->SetNdivisions(505);
  h3_3->GetYaxis()->SetTitleSize(20);
  h3_3->GetYaxis()->SetTitleFont(43);
  h3_3->GetYaxis()->SetTitleOffset(1.5);
  h3_3->GetYaxis()->SetLabelFont(43); 
  h3_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h3_3->GetXaxis()->SetTitle("Length of Track (cm)");
  h3_3->GetXaxis()->SetTitleSize(20);
  h3_3->GetXaxis()->SetTitleFont(43);
  h3_3->GetXaxis()->SetTitleOffset(4);
  h3_3->GetXaxis()->SetLabelFont(43); 
  h3_3->GetXaxis()->SetLabelSize(15);

  c3->Print("analysis1_1/MCC9_length_tag1_all.png");
  
  ///////////////////////////////////////////////////////////////
  //NOW HERE IS CANVAS 4
  //////////////////////////////////////////////////////////////
  TCanvas *c4= new TCanvas("c4","X Coordinate of Vertex",1500,1000);
  c4->cd(1);
  
  THStack *hs4 = new THStack("hs4","X Coordinate of Vertex");
  TPad *pad7 = new TPad("pad7", "pad7", 0, 0.3, 1, 1.0);
  pad7->SetBottomMargin(0);
  pad7->SetGridx();
  pad7->Draw();            
  pad7->cd();               
  hs4->SetTitle("X Coordinate of Vertex; x (cm) ;# of Events");
  hs4->Add(h4);
  hs4->Add(h4_2);
  hs4->Draw("hist");
  h4->SetLineColor(kRed+2);
  h4->SetFillColor(kRed);
  h4->SetLineWidth(1);
  h4_2->SetLineColor(kBlue+2);
  h4_2->SetLineWidth(1);
  h4_2->SetFillColor(kBlue);
  h4_2->SetFillStyle(3005);
  hs4->GetYaxis()->SetTitleSize(20);
  hs4->GetYaxis()->SetTitleFont(43);
  hs4->GetYaxis()->SetTitleOffset(1.5);
  //hs4->SetMaximum(150);
  
  //h4->Draw("hist");
  h4_1->Draw("e1SAME");
  //h4->SetTitle("X Coordinate of Vertex; x (cm) ;# of Events");
  h4_1->SetLineColor(kBlack);
  h4_1->SetLineWidth(2);
  //h4->SetStats(kFALSE);
  //h4->SetFillColor(kRed);

  auto legend_4 = new TLegend(0.8,0.8,0.9,0.9);
  legend_4->AddEntry(h4,"MC Tag 1","pf");
  legend_4->AddEntry(h4_1,"BNB Tag 1","lepf");
  legend_4->AddEntry(h4_2, "EXT Tag 1","pf");
  legend_4->SetTextFont(42);
  legend_4->Draw();

  c4->cd();      
  TPad *pad8 = new TPad("pad8", "pad8", 0, 0.05, 1, 0.3);
  pad8->SetTopMargin(0);
  pad8->SetBottomMargin(0.2);
  pad8->SetGridx(); 
  pad8->Draw();
  pad8->cd();       
  TH1F *h4_3 = (TH1F*)h4_1->Clone("h4_3");
  TH1F *h4_4 = (TH1F*)h4_2->Clone("h4_4");
  h4_4->Add(h4);
  h4_3->Divide(h4_3,h4_4,1,1,"B");
  h4_3->Draw("e1p");
  //h4_3->SetMinimum(0);  
  //h4_3->SetMaximum(2.2); 
  h4_3->SetStats(kFALSE);
  h4_3->SetTitle("");

  TF1 *a4 = new TF1("a4","1", 0 , 300);
  a4->SetLineColor(kRed+2);
  a4->Draw("SAME");

  // Y axis ratio plot settings
  h4_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h4_3->GetYaxis()->SetNdivisions(505);
  h4_3->GetYaxis()->SetTitleSize(20);
  h4_3->GetYaxis()->SetTitleFont(43);
  h4_3->GetYaxis()->SetTitleOffset(1.5);
  h4_3->GetYaxis()->SetLabelFont(43); 
  h4_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h4_3->GetXaxis()->SetTitle("x (cm)");
  h4_3->GetXaxis()->SetTitleSize(20);
  h4_3->GetXaxis()->SetTitleFont(43);
  h4_3->GetXaxis()->SetTitleOffset(4);
  h4_3->GetXaxis()->SetLabelFont(43); 
  h4_3->GetXaxis()->SetLabelSize(15);

  c4->Print("analysis1_1/MCC9_x_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 5
  //////////////////////
  TCanvas *c5= new TCanvas("c5"," Y Coordinate of Vertex",1500,1000);
  c5->cd(1);
  
  THStack *hs5 = new THStack("hs5","Y Coordinate of Vertex");
  TPad *pad9 = new TPad("pad9", "pad9", 0, 0.3, 1, 1.0);
  pad9->SetBottomMargin(0);
  pad9->SetGridx();
  pad9->Draw();            
  pad9->cd(); 
  hs5->SetTitle("Y Coordinate of Vertex; y (cm) ;# of Events");
  hs5->Add(h5);
  hs5->Add(h5_2);
  hs5->Draw("hist");
  h5->SetLineColor(kRed+2);
  h5->SetFillColor(kRed);
  h5->SetLineWidth(1);
  h5_2->SetLineColor(kBlue+2);
  h5_2->SetLineWidth(1);
  h5_2->SetFillColor(kBlue);
  h5_2->SetFillStyle(3005);
  hs5->GetYaxis()->SetTitleOffset(1.3);
  hs5->GetYaxis()->SetTitleSize(20);
  hs5->GetYaxis()->SetTitleFont(43);
  hs5->GetYaxis()->SetTitleOffset(1.5);
  hs5->SetMaximum(750);
 
  // h5->Draw("hist");
  h5_1->Draw("e1SAME");
  //h5->SetTitle("Y Coordinate of Vertex; y (cm) ;# of Events");
  h5_1->SetLineColor(kBlack);
  h5_1->SetLineWidth(2);
  h5->SetStats(kFALSE);
  h5->SetFillColor(kRed);

  auto legend_5 = new TLegend(0.8,0.8,0.9,0.9);
  legend_5->AddEntry(h5,"MC Tag 1","pf");
  legend_5->AddEntry(h5_1,"BNB Tag 1","lepf");
  legend_5->AddEntry(h5_2, "EXT Tag 1","pf");
  legend_5->SetTextFont(42);
  legend_5->Draw();
  
  c5->cd();      
  TPad *pad10 = new TPad("pad10", "pad10", 0, 0.05, 1, 0.3);
  pad10->SetTopMargin(0);
  pad10->SetBottomMargin(0.2);
  pad10->SetGridx(); 
  pad10->Draw();
  pad10->cd();       
  TH1F *h5_3 = (TH1F*)h5_1->Clone("h5_3");
  TH1F *h5_4 = (TH1F*)h5_2->Clone("h5_4");
  h5_4->Add(h5);
  h5_3->Divide(h5_3,h5_4,1,1,"B");
  h5_3->Draw("e1p");
  //h5_3->SetMinimum(-1);  
  //h5_3->SetMaximum(2.5); 
  h5_3->SetStats(kFALSE);
  h5_3->SetTitle("");

  TF1 *a5 = new TF1("a5","1", -125 , 125);
  a5->SetLineColor(kRed+2);
  a5->Draw("SAME");

  // Y axis ratio plot settings
  h5_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h5_3->GetYaxis()->SetNdivisions(505);
  h5_3->GetYaxis()->SetTitleSize(20);
  h5_3->GetYaxis()->SetTitleFont(43);
  h5_3->GetYaxis()->SetTitleOffset(1.5);
  h5_3->GetYaxis()->SetLabelFont(43); 
  h5_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h5_3->GetXaxis()->SetTitle("y (cm)");
  h5_3->GetXaxis()->SetTitleSize(20);
  h5_3->GetXaxis()->SetTitleFont(43);
  h5_3->GetXaxis()->SetTitleOffset(4);
  h5_3->GetXaxis()->SetLabelFont(43); 
  h5_3->GetXaxis()->SetLabelSize(15);

  c5->Print("analysis1_1/MCC9_y_tag1_all.png");
   
  //////////////////////
  //NOW HERE IS CANVAS 6
  //////////////////////
  TCanvas *c6= new TCanvas("c6","Z Coordinate of Vertex",1500,1000);
  c6->cd(1);
  
  THStack *hs6 = new THStack("hs6","Z Coordinate of Vertex");
  TPad *pad11 = new TPad("pad11", "pad11", 0, 0.3, 1, 1.0);
  pad11->SetBottomMargin(0);
  pad11->SetGridx();
  pad11->Draw();            
  pad11->cd(); 
  hs6->SetTitle("Z Coordinate of Vertex; z (cm) ;# of Events");
  hs6->Add(h6);
  hs6->Add(h6_2);
  hs6->Draw("hist");
  h6->SetLineColor(kRed+2);
  h6->SetFillColor(kRed);
  h6->SetLineWidth(1);
  h6_2->SetLineColor(kBlue+2);
  h6_2->SetLineWidth(1);
  h6_2->SetFillColor(kBlue);
  h6_2->SetFillStyle(3005);
  hs6->GetYaxis()->SetTitleOffset(1.3);
  hs6->GetYaxis()->SetTitleSize(20);
  hs6->GetYaxis()->SetTitleFont(43);
  hs6->GetYaxis()->SetTitleOffset(1.5);
  hs6->SetMaximum(650);

  //h6->Draw("hist");
  h6_1->Draw("e1SAME");
  //h6->SetTitle("Z Coordinate of Vertex; z (cm) ;# of Events");
  h6_1->SetLineColor(kBlack);
  h6_1->SetLineWidth(2);
  //h6->SetStats(kFALSE);
  //h6->SetFillColor(kRed);

  auto legend_6 = new TLegend(0.8,0.8,0.9,0.9);
  legend_6->AddEntry(h6,"MC Tag 1","pf");
  legend_6->AddEntry(h6_1,"BNB Tag 1","lepf");
  legend_6->AddEntry(h6_2, "EXT Tag 1","pf");
  legend_6->SetTextFont(42);
  legend_6->Draw();
  
  c6->cd();      
  TPad *pad12 = new TPad("pad12", "pad12", 0, 0.05, 1, 0.3);
  pad12->SetTopMargin(0);
  pad12->SetBottomMargin(0.2);
  pad12->SetGridx(); 
  pad12->Draw();
  pad12->cd();       
  TH1F *h6_3 = (TH1F*)h6_1->Clone("h6_3");
  TH1F *h6_4 = (TH1F*)h6_2->Clone("h6_4");
  h6_4->Add(h6);
  h6_3->Divide(h6_3,h6_4,1,1,"B");
  h6_3->Draw("e1p");
  //h6_3->SetMinimum(0.3);  
  //h6_3->SetMaximum(3.0); 
  h6_3->SetStats(kFALSE);
  h6_3->SetTitle("");

  TF1 *a6 = new TF1("a6","1", 0 , 1050);
  a6->SetLineColor(kRed+2);
  a6->Draw("SAME");

  // Y axis ratio plot settings
  h6_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h6_3->GetYaxis()->SetNdivisions(505);
  h6_3->GetYaxis()->SetTitleSize(20);
  h6_3->GetYaxis()->SetTitleFont(43);
  h6_3->GetYaxis()->SetTitleOffset(1.5);
  h6_3->GetYaxis()->SetLabelFont(43); 
  h6_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h6_3->GetXaxis()->SetTitle("z (cm)");
  h6_3->GetXaxis()->SetTitleSize(20);
  h6_3->GetXaxis()->SetTitleFont(43);
  h6_3->GetXaxis()->SetTitleOffset(4);
  h6_3->GetXaxis()->SetLabelFont(43); 
  h6_3->GetXaxis()->SetLabelSize(15);

  c6->Print("analysis1_1/MCC9_z_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 7
  //////////////////////
  TCanvas *c7= new TCanvas("c7","Shower Multiplicity",1500,1000);
  c7->cd(1);
  
  THStack *hs7 = new THStack("hs7","Shower Multiplicity");
  TPad *pad17 = new TPad("pad17", "pad17", 0, 0.3, 1, 1.0);
  pad17->SetBottomMargin(0);
  pad17->SetGridx();
  pad17->Draw();            
  pad17->cd();
  hs7->SetTitle("Shower Multiplicity; Multiplicity ;# of Events");
  hs7->Add(h7);
  hs7->Add(h7_2);
  hs7->Draw("hist");
  h7->SetLineColor(kRed+2);
  h7->SetFillColor(kRed);
  h7->SetLineWidth(1);
  h7_2->SetLineColor(kBlue+2);
  h7_2->SetLineWidth(1);
  h7_2->SetFillColor(kBlue);
  h7_2->SetFillStyle(3005);
  hs7->GetYaxis()->SetTitleOffset(1.3);
  hs7->GetYaxis()->SetTitleSize(20);
  hs7->GetYaxis()->SetTitleFont(43);
  hs7->GetYaxis()->SetTitleOffset(1.5);
  //hs7->SetMaximum(2000);
  
  //h9->Draw("hist");
  h7_1->Draw("e1SAME");
  //h9->SetTitle("Track Multiplicity; mult ;# of Events");
  h7_1->SetLineColor(kBlack);
  h7_1->SetLineWidth(2);
  //h9->SetStats(kFALSE);
  //h9->SetFillColor(kRed);

  auto legend_7 = new TLegend(0.8,0.8,0.9,0.9);
  legend_7->AddEntry(h7,"MC Tag 1","pf");
  legend_7->AddEntry(h7_1,"BNB Tag 1","lepf");
  legend_7->AddEntry(h7_2, "EXT Tag 1","pf");
  legend_7->SetTextFont(42);
  legend_7->Draw();

  c7->cd();      
  TPad *pad18 = new TPad("pad18", "pad18", 0, 0.05, 1, 0.3);
  pad18->SetTopMargin(0);
  pad18->SetBottomMargin(0.2);
  pad18->SetGridx(); 
  pad18->Draw();
  pad18->cd();       
  TH1F *h7_3 = (TH1F*)h7_1->Clone("h7_3");
  TH1F *h7_4 = (TH1F*)h7_2->Clone("h7_4");
  h7_4->Add(h7);
  h7_3->Divide(h7_3,h7_4,1,1,"B");
  h7_3->Draw("e1p");
  //h7_3->SetMinimum(0);  
  //h7_3->SetMaximum(3.5); 
  h7_3->SetStats(kFALSE);
  h7_3->SetTitle("");

  TF1 *a7 = new TF1("a7","1", 0 , 10);
  a7->SetLineColor(kRed+2);
  a7->Draw("SAME");

  // Y axis ratio plot settings
  h7_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h7_3->GetYaxis()->SetNdivisions(505);
  h7_3->GetYaxis()->SetTitleSize(20);
  h7_3->GetYaxis()->SetTitleFont(43);
  h7_3->GetYaxis()->SetTitleOffset(1.5);
  h7_3->GetYaxis()->SetLabelFont(43); 
  h7_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h7_3->GetXaxis()->SetTitle("Multiplicity");
  h7_3->GetXaxis()->SetTitleSize(20);
  h7_3->GetXaxis()->SetTitleFont(43);
  h7_3->GetXaxis()->SetTitleOffset(4);
  h7_3->GetXaxis()->SetLabelFont(43); 
  h7_3->GetXaxis()->SetLabelSize(15);

  c7->Print("analysis1_1/MCC9_showermult_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 8
  //////////////////////
  TCanvas *c8= new TCanvas("c8","PFP Multiplicity",1500,1000);
  c8->cd(1);
  
  THStack *hs8 = new THStack("hs8","PFP Multiplicity");
  TPad *pad13 = new TPad("pad13", "pad13", 0, 0.3, 1, 1.0);
  pad13->SetBottomMargin(0);
  pad13->SetGridx();
  pad13->Draw();            
  pad13->cd();
  hs8->SetTitle("PFP Multiplicity; mult ;# of Events");
  hs8->Add(h8);
  hs8->Add(h8_2);
  hs8->Draw("hist");
  h8->SetLineColor(kRed+2);
  h8->SetFillColor(kRed);
  h8->SetLineWidth(1);
  h8_2->SetLineColor(kBlue+2);
  h8_2->SetLineWidth(1);
  h8_2->SetFillColor(kBlue);
  h8_2->SetFillStyle(3005);
  hs8->GetYaxis()->SetTitleOffset(1.3);
  hs8->GetYaxis()->SetTitleSize(20);
  hs8->GetYaxis()->SetTitleFont(43);
  hs8->GetYaxis()->SetTitleOffset(1.5);
  //hs8->SetMaximum(1500);

  // h8->Draw("hist");
  h8_1->Draw("e1SAME");
  //h8->SetTitle("PFP Multiplicity; mult ;# of Events");
  h8_1->SetLineColor(kBlack);
  h8_1->SetLineWidth(2);
  //h8->SetStats(kFALSE);
  //h8->SetFillColor(kRed);

  auto legend_8 = new TLegend(0.8,0.8,0.9,0.9);
  legend_8->AddEntry(h8,"MC Tag 1","pf");
  legend_8->AddEntry(h8_1,"BNB Tag 1","lepf");
  legend_8->AddEntry(h8_2, "EXT Tag 1","pf");
  legend_8->SetTextFont(42);
  legend_8->Draw();
  
  c8->cd();      
  TPad *pad14 = new TPad("pad14", "pad14", 0, 0.05, 1, 0.3);
  pad14->SetTopMargin(0);
  pad14->SetBottomMargin(0.2);
  pad14->SetGridx(); 
  pad14->Draw();
  pad14->cd();       
  TH1F *h8_3 = (TH1F*)h8_1->Clone("h8_3");
  TH1F *h8_4 = (TH1F*)h8_2->Clone("h8_4");
  h8_4->Add(h8);
  h8_3->Divide(h8_3,h8_4,1,1,"B");
  h8_3->Draw("e1p");
  // h8_3->SetMinimum(-2);  
  //h8_3->SetMaximum(6.5); 
  h8_3->SetStats(kFALSE);
  h8_3->SetTitle("");

  TF1 *a8 = new TF1("a8","1", 0 , 10);
  a8->SetLineColor(kRed+2);
  a8->Draw("SAME");

  // Y axis ratio plot settings
  h8_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h8_3->GetYaxis()->SetNdivisions(505);
  h8_3->GetYaxis()->SetTitleSize(20);
  h8_3->GetYaxis()->SetTitleFont(43);
  h8_3->GetYaxis()->SetTitleOffset(1.5);
  h8_3->GetYaxis()->SetLabelFont(43); 
  h8_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h8_3->GetXaxis()->SetTitle("Multiplicity");
  h8_3->GetXaxis()->SetTitleSize(20);
  h8_3->GetXaxis()->SetTitleFont(43);
  h8_3->GetXaxis()->SetTitleOffset(4);
  h8_3->GetXaxis()->SetLabelFont(43); 
  h8_3->GetXaxis()->SetLabelSize(15);

  c8->Print("analysis1_1/MCC9_pfpmult_tag1_all.png");
  
  //////////////////////
  //NOW HERE IS CANVAS 9
  //////////////////////
  TCanvas *c9= new TCanvas("c9","Track Multiplicity",1500,1000);
  c9->cd(1);
  
  THStack *hs9 = new THStack("hs9","Track Multiplicity");
  TPad *pad15 = new TPad("pad15", "pad15", 0, 0.3, 1, 1.0);
  pad15->SetBottomMargin(0);
  pad15->SetGridx();
  pad15->Draw();            
  pad15->cd();
  hs9->SetTitle("Track Multiplicity; mult ;# of Events");
  hs9->Add(h9);
  hs9->Add(h9_2);
  hs9->Draw("hist");
  h9->SetLineColor(kRed+2);
  h9->SetFillColor(kRed);
  h9->SetLineWidth(1);
  h9_2->SetLineColor(kBlue+2);
  h9_2->SetLineWidth(1);
  h9_2->SetFillColor(kBlue);
  h9_2->SetFillStyle(3005);
  hs9->GetYaxis()->SetTitleOffset(1.3);
  hs9->GetYaxis()->SetTitleSize(20);
  hs9->GetYaxis()->SetTitleFont(43);
  hs9->GetYaxis()->SetTitleOffset(1.5);
  //hs9->SetMaximum(9000);
  
  //h9->Draw("hist");
  h9_1->Draw("e1SAME");
  //h9->SetTitle("Track Multiplicity; mult ;# of Events");
  h9_1->SetLineColor(kBlack);
  h9_1->SetLineWidth(2);
  //h9->SetStats(kFALSE);
  //h9->SetFillColor(kRed);

  auto legend_9 = new TLegend(0.8,0.8,0.9,0.9);
  legend_9->AddEntry(h9,"MC Tag 1","pf");
  legend_9->AddEntry(h9_1,"BNB Tag 1","lepf");
  legend_9->AddEntry(h9_2, "EXT Tag 1","pf");
  legend_9->SetTextFont(42);
  legend_9->Draw();

  c9->cd();      
  TPad *pad16 = new TPad("pad16", "pad16", 0, 0.05, 1, 0.3);
  pad16->SetTopMargin(0);
  pad16->SetBottomMargin(0.2);
  pad16->SetGridx(); 
  pad16->Draw();
  pad16->cd();       
  TH1F *h9_3 = (TH1F*)h9_1->Clone("h9_3");
  TH1F *h9_4 = (TH1F*)h9_2->Clone("h9_4");
  h9_4->Add(h9);
  h9_3->Divide(h9_3,h9_4,1,1,"B");
  h9_3->Draw("e1p");
  //h9_3->SetMinimum(-5);  
  //h9_3->SetMaximum(15); 
  h9_3->SetStats(kFALSE);
  h9_3->SetTitle("");

  TF1 *a9 = new TF1("a9","1", 0 , 10);
  a9->SetLineColor(kRed+2);
  a9->Draw("SAME");

  // Y axis ratio plot settings
  h9_3->GetYaxis()->SetTitle("BNB/(EXT+MC)");
  h9_3->GetYaxis()->SetNdivisions(505);
  h9_3->GetYaxis()->SetTitleSize(20);
  h9_3->GetYaxis()->SetTitleFont(43);
  h9_3->GetYaxis()->SetTitleOffset(1.5);
  h9_3->GetYaxis()->SetLabelFont(43); 
  h9_3->GetYaxis()->SetLabelSize(15);
  // X axis ratio plot settings
  h9_3->GetXaxis()->SetTitle("Multiplicity");
  h9_3->GetXaxis()->SetTitleSize(20);
  h9_3->GetXaxis()->SetTitleFont(43);
  h9_3->GetXaxis()->SetTitleOffset(4);
  h9_3->GetXaxis()->SetLabelFont(43); 
  h9_3->GetXaxis()->SetLabelSize(15);

  c9->Print("analysis1_1/MCC9_trackmult_tag1_all.png");
  
}
