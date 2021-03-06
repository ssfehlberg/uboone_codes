#define bnb_rolling_tag0_cxx
#include "bnb_rolling_tag0.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>

void bnb_rolling_tag0::Loop()
{
  TFile *tfile = new TFile("bnb_rolling_tag0_histos.root","RECREATE");
  int flashInBeamSpill = -1;
  int _gainCalib = 198;
  int _pe_cut =50;
  double _beamSpillStarts=3.30;
  double _beamSpillEnds=4.90;
  int nEvtsWFlashInBeamSpill = 0;

  //////////////////STUFF FROM ALL  SLICES////////////////

  // All the things for the x,y,z coordinates of the vertex
  TH1D * h_vertex_x_bnb = new TH1D("h_vertex_x_bnb","Vetex_x_bnb",40,0,275);
  TH1D * h_vertex_y_bnb = new TH1D("h_vertex_y_bnb","Vetex_y_bnb",40,-125,125);
  TH1D * h_vertex_z_bnb = new TH1D("h_vertex_z_bnb","Vetex_z_bnb",50,0,1050);

  // All the things for th muon candidate 
  TH1D * h_cos_truth_theta_muon_bnb = new TH1D("h_cos_truth_theta_muon_bnb","Muon_cos(theta)_bnb",25,-1,1);
  TH1D * h_truth_phi_muon_bnb = new TH1D("h_truth_phi_muon_bnb","Muon_phi_bnb",20,-3.15,3.15);
  TH1D * h_muon_length_bnb = new TH1D("h_muon_length_bnb","Muon_Length_bnb",30,0,700);

  // All the other things Lu asked for multiplicity
  TH1D * h_pfp_bnb = new TH1D("h_pfp_bnb","PFp_bnb",10,0,10);
  TH1D * h_track_bnb = new TH1D("h_track_bnb","track_bnb",10,0,10);
  TH1D * h_shower_bnb = new TH1D("h_shower_bnb","shower_ext",10,0,10);

  //The true vertex
  //TH1D * h_t_vertex_x_bnb = new TH1D("h_t_vertex_x_bnb","Vertex_x_bnb",40,-275,275);
  //TH1D * h_t_vertex_y_bnb = new TH1D("h_t_vertex_y_bnb","Vertex_y_bnb",40,-125,125);
  //TH1D * h_t_vertex_z_bnb = new TH1D("h_t_vertex_z_bnb","Vertex_z_bnb",50,-1050,1050);

  //TH1D * h_mag_bnb = new TH1D("h_mag_bnb","Magnitude",50,-1050,1050);
  
  //Other Variables for the Momentum and stuff
  TH1D * h_fls_t_bnb=new TH1D("h_fls_t_bnb","h_fls_t_bnb",100,0,25);
  TH1D * h_fls_pe_bnb=new TH1D("h_fls_pe_bnb","h_fls_pe_bnb",130,0,6500);
  TH1D * h_QLLx_TPCx_bnb=new TH1D("h_QLLx_TPCx_bnb","h_QLLx_TPCx_bnb",200,-200,200);
  TH1D * h_hypoz_flsz_bnb=new TH1D("h_hypoz_flsz_bnb","h_hypoz_flsz_bnb",100,-1000,1000);
  TH2D * h_true_reco_mom_mcs_bnb = new TH2D("h_true_reco_mom_mcs_bnb", ";Muon Momentum (Truth) [GeV]; Muon Momentum (MCS) [GeV]",40,0,2,40,0,2);
  TH2D * h_true_reco_mom_range_bnb = new TH2D("h_true_reco_mom_range_bnb", ";Muon Momentum (Truth) [GeV]; Muon Momentum (range) [GeV]",40,0,2,40,0,2);
 
  TH1D * h_muon_mom_bnb = new TH1D("h_muon_mom_bnb","Muon_mom_bnb",50,-2.5,2.5);
  TH1D * h_muon_mom_diff_bnb = new TH1D("h_muon_mom_diff_bnb","h_muon_mom_diff_bnb",50,-2.5,2.5);

  ////DA LOOP!
   if (fChain == 0) return;
   Long64_t nentries = fChain->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   cout << "Total # of Events:" << nentries<<endl;
   //cout<<nslices<<endl;
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = fChain->GetEntry(jentry);   nbytes += nb;
      if(nslices==0) continue;
      //BeamFlash Cut Stuff
      if (nbeamfls == 0) continue;
      int flashInBeamSpill = -1;
      double old_pe = -1;
      for (int fls = 0; fls < nbeamfls; fls ++)
	{
	  if(beamfls_pe.at(fls) >= 50)
	    {
	      h_fls_t_bnb->Fill(beamfls_time.at(fls));
	      h_fls_pe_bnb->Fill(beamfls_pe.at(fls));
	    }
	}


      
      for (int fls = 0; fls < nbeamfls; fls ++){
	  if (beamfls_time.at(fls) > _beamSpillStarts && beamfls_time.at(fls) < _beamSpillEnds) {
	  if (beamfls_pe.at(fls) >= _pe_cut) {
	    if (beamfls_pe.at(fls) > old_pe) {
	      flashInBeamSpill = fls;
	      old_pe = beamfls_pe.at(fls);
	    }
	    nEvtsWFlashInBeamSpill++;
	  }
	}
      }
      if (flashInBeamSpill == -1) continue;
      h_QLLx_TPCx_bnb->Fill(slc_flsmatch_qllx.at(0)-slc_flsmatch_tpcx.at(0));
      //cout<<slc_flsmatch_qllx.at(0)-slc_flsmatch_tpcx.at(0)<<endl;
	h_hypoz_flsz_bnb->Fill(slc_flsmatch_hypoz.at(0) - beamfls_z.at(flashInBeamSpill));

      //For loop to evaluate the slices!
      for(int slc = 0; slc < nslices; slc ++){

	//FM delta x Cuts
	if(slc_flsmatch_qllx.at(slc) - slc_flsmatch_tpcx.at(slc) > 50) continue;
	if(slc_flsmatch_qllx.at(slc) - slc_flsmatch_tpcx.at(slc) < -100) continue;

	//FM delta z cuts
	//if(slc_flsmatch_hypoz.at(slc) - beamfls_z.at(flashInBeamSpill) > 75) continue;
	//if(slc_flsmatch_hypoz.at(slc) - beamfls_z.at(flashInBeamSpill) < -75) continue;

	//Quality Cuts
	if (slc_muoncandidate_residuals_std.at(slc) > 2.5) continue;
	if (std::abs(slc_muoncandidate_residuals_mean.at(slc)) > 0.7) continue;
	if (slc_muoncandidate_perc_used_hits_in_cluster.at(slc) < 0.7) continue;
	if(slc_muoncandidate_contained.at(slc))
	  {
	    h_muon_mom_diff_bnb->Fill(slc_muoncandidate_mom_mcs.at(slc) - slc_muoncandidate_mom_range.at(slc));
	  }

	//MCS-Length Cuts
	if(slc_muoncandidate_contained.at(slc) && (slc_muoncandidate_mom_mcs.at(slc) - slc_muoncandidate_mom_range.at(slc) > 0.2)) continue;
	
       //Cuts for MIP Consistency
	std::vector<double> svm_x = {86300, 86050, 85850, 85600, 85400, 85150, 84950, 84700, 84500, 84300, 84100, 83850, 83650, 83450, 83250, 83050, 82850, 82650, 82450, 82250, 82050, 81900, 81700, 81500, 81300, 81150, 80950, 80750, 80600, 80400, 80250, 80050, 79900, 79750, 79550, 79400, 79250, 79050, 78900, 78750, 78600, 78400, 78250, 78100, 77950, 77800, 77650, 77500, 77350, 77200, 77050, 76900, 76750, 76650, 76500, 76350, 76200, 76050, 75950, 75800, 75650, 75550, 75400, 75300, 75150, 75000, 74900, 74750, 74650, 74500, 74400, 74250, 74150, 74050, 73900, 73800, 73700, 73550, 73450, 73350, 73250, 73100, 73000, 72900, 72800, 72700, 72550, 72450, 72350, 72250, 72150, 72050, 71950, 71850, 71750, 71650, 71550, 71450, 71350, 71250, 71150, 71100, 71000, 70900, 70800, 70700, 70600, 70550, 70450, 70350, 70250, 70200, 70100, 70000, 69950, 69850, 69750, 69700, 69600, 69550, 69450, 69350, 69300, 69200, 69150, 69050, 69000, 68900, 68850, 68750, 68700, 68600, 68550, 68500, 68400, 68350, 68250, 68200, 68150, 68050, 68000, 67950, 67850, 67800, 67750, 67700, 67600, 67550, 67500, 67450, 67350, 67300, 67250, 67200, 67150, 67100, 67000, 66950, 66900, 66850, 66800, 66750, 66700, 66650, 66600, 66550, 66500, 66450, 66400, 66350, 66300, 66250, 66200, 66150, 66100, 66050, 66000, 65950, 65900, 65850, 65800, 65750, 65750, 65700, 65650, 65600, 65550, 65500, 65450, 65450, 65400, 65350, 65300, 65250, 65250, 65200, 65150, 65100, 65100, 65050, 65000, 65000, 64950, 64900, 64850, 64850, 64800, 64750, 64750, 64700, 64700, 64650, 64600, 64600, 64550, 64500, 64500, 64450, 64450, 64400, 64400, 64350, 64350, 64300, 64250, 64250, 64200, 64200, 64150, 64150, 64100, 64100, 64100, 64050, 64050, 64000, 64000, 63950, 63950, 63900, 63900, 63900, 63850, 63850, 63800, 63800, 63800, 63750, 63750, 63750, 63700, 63700, 63700, 63650, 63650, 63650, 63600, 63600, 63600, 63550, 63550, 63550, 63500, 63500, 63500, 63500, 63450, 63450, 63450, 63450, 63400, 63400, 63400, 63400, 63400, 63350, 63350, 63350, 63350, 63350, 63350, 63300, 63300, 63300, 63300, 63300, 63300, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63200, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63250, 63300, 63300, 63300, 63300, 63300, 63300, 63300, 63350, 63350, 63350, 63350, 63350, 63350, 63400, 63400, 63400, 63400, 63400, 63400, 63450, 63450, 63450, 63450, 63500, 63500, 63500, 63500, 63500, 63550, 63550, 63550, 63550, 63600, 63600, 63600, 63600, 63650, 63650, 63650, 63650, 63700, 63700, 63700, 63750, 63750, 63750, 63800, 63800, 63800, 63800, 63850, 63850, 63850, 63900, 63900, 63900, 63950, 63950, 63950, 64000, 64000, 64000, 64050, 64050, 64100, 64100, 64100, 64150, 64150, 64150, 64200, 64200, 64250, 64250, 64250, 64300, 64300, 64350, 64350, 64350, 64400, 64400, 64450, 64450, 64450, 64500, 64500, 64550, 64550, 64600, 64600, 64650, 64650, 64650, 64700, 64700, 64750, 64750, 64800, 64800, 64850, 64850, 64900, 64900, 64950, 64950, 65000, 65000, 65050, 65050, 65100, 65100, 65150, 65150, 65200, 65200, 65250, 65250, 65300, 65300, 65350, 65350, 65400, 65400, 65450, 65500, 65500, 65550, 65550, 65600, 65600, 65650, 65650, 65700, 65750, 65750, 65800, 65800, 65850, 65850, 65900, 65950, 65950, 66000, 66000, 66050, 66100, 66100, 66150, 66150, 66200, 66250, 66250, 66300, 66350, 66350, 66400, 66400, 66450, 66500, 66500, 66550, 66600, 66600, 66650, 66700, 66700, 66750, 66750, 66800, 66850, 66850, 66900, 66950, 66950, 67000, 67050, 67050, 67100, 67150, 67150, 67200, 67250, 67300, 67300, 67350, 67400, 67400, 67450, 67500, 67500, 67550, 67600, 67650, 67650, 67700, 67750, 67750, 67800, 67850, 67900, 67900, 67950, 68000, 68050, 68050, 68100, 68150, 68150, 68200, 68250, 68300, 68300, 68350, 68400, 68450, 68450, 68500, 68550, 68600, 68650, 68650, 68700, 68750, 68800, 68800, 68850, 68900, 68950, 69000, 69000, 69050, 69100, 69150, 69150, 69200, 69250, 69300, 69350, 69350, 69400, 69450, 69500, 69550, 69600, 69600, 69650, 69700, 69750, 69800, 69800, 69850, 69900, 69950, 70000, 70050, 70050, 70100, 70150, 70200, 70250, 70300, 70300, 70350, 70400, 70450, 70500, 70550, 70600, 70600, 70650, 70700, 70750, 70800, 70850, 70900, 70900, 70950, 71000, 71050, 71100, 71150, 71200, 71250, 71300, 71300, 71350, 71400, 71450, 71500, 71550, 71600, 71650, 71700, 71700, 71750, 71800, 71850, 71900, 71950, 72000, 72050, 72100, 72150, 72200, 72200, 72250, 72300, 72350, 72400, 72450, 72500, 72550, 72600, 72650, 72700, 72750, 72800, 72850, 72850, 72900, 72950, 73000, 73050, 73100, 73150, 73200, 73250, 73300, 73350, 73400, 73450, 73500, 73550, 73600, 73650, 73700, 73750, 73800, 73850, 73900, 73900, 73950, 74000, 74050, 74100, 74150, 74200, 74250, 74300, 74350, 74400, 74450, 74500, 74550, 74600, 74650, 74700, 74750, 74800, 74850, 74900, 74950, 75000, 75050, 75100, 75150, 75200, 75250, 75300, 75350, 75400, 75450, 75500, 75550, 75600, 75650, 75700, 75750, 75800, 75850, 75900, 76000, 76050, 76100, 76150, 76200, 76250, 76300, 76350, 76400, 76450, 76500, 76550, 76600, 76650, 76700, 76750, 76800, 76850, 76900, 76950, 77000, 77050, 77100, 77200, 77250, 77300, 77350, 77400, 77450, 77500, 77550, 77600, 77650, 77700, 77750, 77800, 77850, 77900, 78000, 78050, 78100, 78150, 78200, 78250, 78300, 78350, 78400, 78450, 78500, 78550, 78600, 78700, 78750, 78800, 78850, 78900, 78950, 79000, 79050, 79100, 79150, 79250, 79300, 79350, 79400, 79450, 79500, 79550, 79600, 79650, 79750, 79800, 79850, 79900, 79950, 80000, 80050, 80100, 80150, 80250, 80300, 80350, 80400, 80450, 80500, 80550, 80600, 80700, 80750, 80800, 80850, 80900, 80950, 81000, 81100, 81150, 81200, 81250, 81300, 81350, 81400, 81450, 81550, 81600, 81650, 81700, 81750, 81800, 81900, 81950, 82000, 82050, 82100, 82150, 82200, 82300, 82350, 82400, 82450, 82500, 82550, 82650, 82700, 82750, 82800, 82850, 82900, 83000, 83050, 83100, 83150, 83200, 83250, 83350, 83400, 83450, 83500, 83550, 83650, 83700, 83750, 83800, 83850, 83900, 84000, 84050, 84100, 84150, 84200, 84300, 84350, 84400, 84450, 84500, 84600, 84650, 84700, 84750, 84800, 84900, 84950, 85000, 85050, 85100, 85200, 85250, 85300, 85350, 85400, 85500, 85550, 85600, 85650, 85700, 85800, 85850, 85900, 85950, 86000, 86100, 86150, 86200, 86250, 86350, 86400, 86450, 86500, 86550, 86650, 86700, 86750, 86800, 86900, 86950, 87000, 87050, 87150, 87200, 87250, 87300, 87350, 87450, 87500, 87550, 87600, 87700, 87750, 87800, 87850, 87950, 88000, 88050, 88100, 88200, 88250, 88300, 88350, 88450, 88500, 88550, 88600, 88700, 88750, 88800, 88850, 88950, 89000, 89050, 89100, 89200, 89250, 89300, 89350, 89450, 89500, 89550, 89600, 89700, 89750, 89800, 89900, 89950, 90000, 90050, 90150, 90200, 90250, 90300, 90400, 90450, 90500, 90600, 90650, 90700, 90750, 90850, 90900, 90950, 91000, 91100, 91150, 91200, 91300, 91350, 91400, 91450, 91550, 91600, 91650, 91750, 91800, 91850, 91950, 92000, 92050, 92100, 92200, 92250};
       
       double dqdx_calib = slc_muoncandidate_dqdx_trunc.at(slc) * _gainCalib;
       double l = std::round(slc_muoncandidate_length.at(slc));
       double dqdx_cut = 200000;
       if (l >= 0 && l < 1000) {
	    dqdx_cut = svm_x.at(l);}
       if (dqdx_calib > dqdx_cut) continue;
	
       //Cuts for the Fudicial Volume
       if(slc_nuvtx_fv.at(slc) == 0) continue;
       if(slc_nuvtx_z.at(slc) > 675 && slc_nuvtx_z.at(slc) < 775) continue;

       //The actual histograms to be filled
       h_vertex_x_bnb->Fill(slc_nuvtx_x.at(slc));
       h_vertex_y_bnb->Fill(slc_nuvtx_y.at(slc));
       h_vertex_z_bnb->Fill(slc_nuvtx_z.at(slc));

       //h_t_vertex_x_bnb->Fill(slc_nuvtx_x.at(slc) - tvtx_x.at(slc));
       //h_t_vertex_y_bnb->Fill(slc_nuvtx_y.at(slc) -tvtx_y.at(slc));
       //h_t_vertex_z_bnb->Fill(slc_nuvtx_z.at(slc) - tvtx_z.at(slc));

       //h_mag_bnb->Fill(pow((pow((slc_nuvtx_x.at(slc) - tvtx_x.at(slc)),2)+pow((slc_nuvtx_y.at(slc) - tvtx_y.at(slc)),2)+pow((slc_nuvtx_z.at(slc) - tvtx_z.at(slc)),2)),1/2));

       h_truth_phi_muon_bnb->Fill(slc_muoncandidate_phi.at(slc));
       h_cos_truth_theta_muon_bnb->Fill(slc_muoncandidate_theta.at(slc));
       h_muon_length_bnb->Fill(slc_muoncandidate_length.at(slc));
	
       h_pfp_bnb->Fill(slc_mult_pfp.at(slc));
       h_track_bnb->Fill(slc_mult_track.at(slc));
       h_shower_bnb->Fill(slc_mult_shower.at(slc));

       h_muon_mom_bnb->Fill(slc_muoncandidate_mom_mcs.at(slc));
       cout<<slc_muoncandidate_length.at(slc)<<"  "<<slc_muoncandidate_mom_mcs.at(slc)<<endl;

   	 }
    
   }


  tfile->cd();
   
  //stuff for all the slices
  
   h_vertex_x_bnb->Write();
   h_vertex_y_bnb->Write();
   h_vertex_z_bnb->Write();

   // h_t_vertex_x_bnb->Write();
   //h_t_vertex_y_bnb->Write();
   //h_t_vertex_z_bnb->Write();

   // h_mag_bnb->Write();
   
   h_truth_phi_muon_bnb->Write();
   h_cos_truth_theta_muon_bnb->Write();
   h_muon_length_bnb->Write();

   h_pfp_bnb->Write();
   h_track_bnb->Write();
   h_shower_bnb->Write();
   
   h_pfp_bnb->Write();
   h_track_bnb->Write();
   h_fls_t_bnb->Write();
   h_fls_pe_bnb->Write();
   h_muon_mom_bnb->Write();
   h_muon_mom_diff_bnb->Write();
   h_QLLx_TPCx_bnb->Write();
   h_hypoz_flsz_bnb->Write();
  
   tfile->Close();

   cout<<"Program ran successfully"<<endl;
}
