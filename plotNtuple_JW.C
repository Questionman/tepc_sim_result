{
    gStyle->SetOptStat(0);
    auto file = new TFile("B1_GCR_proton_initial.root");
    auto tree = (TTree *) file -> Get("B1");

    auto cvs = new TCanvas("cvs","",550,500);

    auto frame = new TH2D("frame","",500,1e-2,1e3,100,0.1,1e6);
    frame -> Draw();
  
    Double_t* xboundary = new Double_t[500];
    for (auto i=0;i<=500;i++)
    {
      xboundary[i]=pow(10,-2+5*i/500.);
    //printf("%f \n",xboundary[i]);
    }
    auto hist = new TH1D("h1",";z (mm);Energy deposit (MeV)",500,xboundary);
    tree -> Draw("LET>>h1","","hist same L B *H");
    hist -> SetLineStyle(2);
    hist -> SetLineWidth(2);
    hist -> SetLineColor(kRed);

    cvs -> SetLogy();
    cvs -> SetLogx();

    auto hist2 = new TH1D("h2",";",500,xboundary);
    auto total_yifi = 0.;
    for (auto ibin = 1; ibin <= 500; ++ibin)
    {
        auto yi = hist -> GetXaxis() -> GetBinCenter(ibin);
        auto fi = hist -> GetBinContent(ibin);
        printf("ibin : %d yi : %f fi : %f\n",ibin, yi, fi);
        hist2->SetBinContent(ibin, yi*fi*100);
        total_yifi += yi*fi;
    }
    for (auto ibin = 1; ibin <=500; ++ibin)
    {
      auto content = (hist2 -> GetBinContent(ibin)) / total_yifi;
      hist2 -> SetBinContent(ibin, content);             
    }
    hist2->Draw("same");
}
