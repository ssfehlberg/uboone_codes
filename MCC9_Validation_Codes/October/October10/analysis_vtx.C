 {

  TFile *f1=new TFile("MC_bnb_only_histos.root");

  TH1D * h4_1 = (TH1D*)f1->Get("h_vertex_x_mc");
  TH1D * h5_1 = (TH1D*)f1->Get("h_vertex_y_mc");
  TH1D * h6_1 = (TH1D*)f1->Get("h_vertex_z_mc");

  TH1D * h4 = (TH1D*)f1->Get("h_t_vertex_x_mc");
  TH1D * h5 = (TH1D*)f1->Get("h_t_vertex_y_mc");
  TH1D * h6 = (TH1D*)f1->Get("h_t_vertex_z_mc");

///////////////////////////////////////////////////////////////
  //NOW HERE IS CANVAS 4
  //////////////////////////////////////////////////////////////
  TCanvas *c4= new TCanvas("c4","X Coordinate of Vertex",600,500);
  c4->cd(1);
  
  //THStack *hs4 = new THStack("hs4","X Coordinate of Vertex");
  //TPad *pad7 = new TPad("pad7", "pad7", 0, 0.3, 1, 1.0);
  //pad7->SetBottomMargin(0);
  //pad7->SetGridx();
  //pad7->Draw();            
  //pad7->cd(); 
  //h4->Add(h4_1,-1);
  h4->SetTitle("X Coordinate of Vertex (Difference); x (cm) ;# of Events");
  h4->Draw("hist");
  h4->SetStats(kFALSE);
  h4->SetLineColor(kRed+2);
  h4->SetFillColor(kRed);
  h4->SetLineWidth(1);
  //h4_2->SetLineColor(kBlue+2);
  //h4_2->SetLineWidth(1);
  //h4_2->SetFillColor(kBlue);
  //h4_2->SetFillStyle(3005);
  h4->GetYaxis()->SetTitleSize(20);
  h4->GetYaxis()->SetTitleFont(43);
  h4->GetYaxis()->SetTitleOffset(1);

  //h4_1->Draw("e1SAME");
  //h4_1->SetLineColor(kBlack);
  //h4_1->SetLineWidth(2);

  auto legend_4 = new TLegend(0.8,0.8,0.9,0.9);
  legend_4->AddEntry(h4,"MC","pf");
  //legend_4->AddEntry(h4_1,"BNB","lepf");
  //legend_4->AddEntry(h4_2, "EXT","pf");
  legend_4->SetTextFont(42);
  legend_4->Draw();

  //////////////////////
  //NOW HERE IS CANVAS 5
  //////////////////////
  TCanvas *c5= new TCanvas("c5"," Y Coordinate of Vertex (Difference)",600,500);
  c5->cd(1);
  
  h5->SetTitle("Y Coordinate of Vertex (Difference); y (cm) ;# of Events");
  //h5->Add(h5_1,-1);
  h5->Draw("hist");
  h5->SetStats(kFALSE);
  h5->SetLineColor(kRed+2);
  h5->SetFillColor(kRed);
  h5->SetLineWidth(1);
  h5->GetYaxis()->SetTitleOffset(1.3);
  h5->GetYaxis()->SetTitleSize(20);
  h5->GetYaxis()->SetTitleFont(43);
  h5->GetYaxis()->SetTitleOffset(1);


  auto legend_5 = new TLegend(0.8,0.8,0.9,0.9);
  legend_5->AddEntry(h5,"MC","pf");
  //legend_5->AddEntry(h5_1,"BNB","lepf");
  //legend_5->AddEntry(h5_2, "EXT","pf");
  legend_5->SetTextFont(42);
  legend_5->Draw();

  //////////////////////
  //NOW HERE IS CANVAS 6
  //////////////////////
  TCanvas *c6= new TCanvas("c6","Z Coordinate of Vertex (Difference)",600,500);
  c6->cd(1);
  
  h6->SetTitle("Z Coordinate of Vertex (Difference); z (cm) ;# of Events");
  //h6->Add(h6_1,-1);
  h6->Draw("hist");
  h6->SetStats(kFALSE);
  h6->SetLineColor(kRed+2);
  h6->SetFillColor(kRed);
  h6->SetLineWidth(1);
  h6->GetYaxis()->SetTitleOffset(1.3);
  h6->GetYaxis()->SetTitleSize(20);
  h6->GetYaxis()->SetTitleFont(43);
  h6->GetYaxis()->SetTitleOffset(1);


  auto legend_6 = new TLegend(0.8,0.8,0.9,0.9);
  legend_6->AddEntry(h6,"MC","pf");
  //legend_6->AddEntry(h6_1,"BNB","lepf");
  //legend_6->AddEntry(h6_2, "EXT","pf");
  legend_6->SetTextFont(42);
  legend_6->Draw();
 
}
