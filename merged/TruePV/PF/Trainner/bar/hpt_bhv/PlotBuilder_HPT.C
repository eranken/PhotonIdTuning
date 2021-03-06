#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/GeneticAlgorithm.h"
#include "TMVA/GeneticFitter.h"
#include "TMVA/IFitterTarget.h"
#include "TMVA/Tools.h"
#include "TMVA/Factory.h"

#include <sstream>
#include <string.h>

void PlotBuilder_HPT(){


  //Read the cuts: 


  ifstream tight;
  ifstream medium;
  ifstream loose;


  tight.open("TightR.txt");
  medium.open("MediumR.txt");
  loose.open("LooseR.txt");


  double isoCL,isoCM,isoCT;
  double isoPL,isoPM,isoPT;
  double isoNL,isoNM,isoNT;
  double sieL,sieM,sieT; 
  double hoeU = 0.05;

  if(tight.is_open()){
    while(!tight.eof()){
      tight>>sieT>>isoCT>>isoNT>>isoPT;
      break;
    }
  }

  
  if(medium.is_open()){
    while(!medium.eof()){
      medium>>sieM>>isoCM>>isoNM>>isoPM;
      break;
    }
  }


  if(loose.is_open()){
    while(!loose.eof()){
      loose>>sieL>>isoCL>>isoNL>>isoPL;
      break;
    }
  }

  //Read the Cuts. Now test them


  TH1F *EffNVTX0 = new TH1F("EffNVTX0","Signal Eff vs NVTX 0",100,0,100);
  TH1F *EffPT0   = new TH1F("EffPT0","Signal Eff vs PT 0",100,0,800);
  TH1F *EffETA0  = new TH1F("EffETA0","Signal Eff vs Eta 0",100,-5,5);
  TH1F *EffPHI0  = new TH1F("EffPHI0","Signal Eff vs PHI 0",100,-4,4);

  TH1F *EffNVTXL = new TH1F("EffNVTXL","Signal Eff vs NVTX L",100,0,100);
  TH1F *EffPTL   = new TH1F("EffPTL","Signal Eff vs PT L",100,0,800);
  TH1F *EffETAL  = new TH1F("EffETAL","Signal Eff vs Eta L",100,-5,5);
  TH1F *EffPHIL  = new TH1F("EffPHIL","Signal Eff vs PHI L",100,-4,4);
  
  TH1F *EffNVTXM = new TH1F("EffNVTXM","Signal Eff vs NVTX M",100,0,100);
  TH1F *EffPTM   = new TH1F("EffPTM","Signal Eff vs PT M",100,0,800);
  TH1F *EffETAM  = new TH1F("EffETAM","Signal Eff vs Eta M",100,-5,5);
  TH1F *EffPHIM  = new TH1F("EffPHIM","Signal Eff vs PHI M",100,-4,4);

  TH1F *EffNVTXT = new TH1F("EffNVTXT","Signal Eff vs NVTX T",100,0,100);
  TH1F *EffPTT   = new TH1F("EffPTT","Signal Eff vs PT T",100,0,800);
  TH1F *EffETAT  = new TH1F("EffETAT","Signal Eff vs Eta T",100,-5,5);
  TH1F *EffPHIT  = new TH1F("EffPHIT","Signal Eff vs PHI T",100,-4,4);

  TH1F *EffNVTX0b = new TH1F("EffNVTX0b","Signal Eff vs NVTX 0",100,0,100);
  TH1F *EffPT0b   = new TH1F("EffPT0b","Signal Eff vs PT 0",100,0,800);
  TH1F *EffETA0b  = new TH1F("EffETA0b","Signal Eff vs Eta 0",100,-5,5);
  TH1F *EffPHI0b  = new TH1F("EffPHI0b","Signal Eff vs PHI 0",100,-4,4);

  TH1F *EffNVTXLb = new TH1F("EffNVTXLb","Signal Eff vs NVTX L",100,0,100);
  TH1F *EffPTLb   = new TH1F("EffPTLb","Signal Eff vs PT L",100,0,800);
  TH1F *EffETALb  = new TH1F("EffETALb","Signal Eff vs Eta L",100,-5,5);
  TH1F *EffPHILb  = new TH1F("EffPHILb","Signal Eff vs PHI L",100,-4,4);
  
  TH1F *EffNVTXMb = new TH1F("EffNVTXMb","Signal Eff vs NVTX M",100,0,100);
  TH1F *EffPTMb   = new TH1F("EffPTMb","Signal Eff vs PT M",100,0,800);
  TH1F *EffETAMb  = new TH1F("EffETAMb","Signal Eff vs Eta M",100,-5,5);
  TH1F *EffPHIMb  = new TH1F("EffPHIMb","Signal Eff vs PHI M",100,-4,4);

  TH1F *EffNVTXTb = new TH1F("EffNVTXTb","Signal Eff vs NVTX T",100,0,100);
  TH1F *EffPTTb  = new TH1F("EffPTTb","Signal Eff vs PT T",100,0,800);
  TH1F *EffETATb  = new TH1F("EffETATb","Signal Eff vs Eta T",100,-5,5);
  TH1F *EffPHITb  = new TH1F("EffPHITb","Signal Eff vs PHI T",100,-4,4);

  // Branch out Cuts

   
  TH1F *EffNVTXs = new TH1F("EffNVTXs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTs  = new TH1F("EffPTs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAs  = new TH1F("EffETAs","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXt = new TH1F("EffNVTXt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTt  = new TH1F("EffPTt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAt  = new TH1F("EffETAt","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXc = new TH1F("EffNVTXc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTc  = new TH1F("EffPTc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAc  = new TH1F("EffETAc","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXn = new TH1F("EffNVTXn","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTn  = new TH1F("EffPTn","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAn  = new TH1F("EffETAn","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXp = new TH1F("EffNVTXp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTp  = new TH1F("EffPTp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAp  = new TH1F("EffETAp","Signal Eff vs PT T s",100,-5,5);


  TH1F *EffNVTXbs = new TH1F("EffNVTXbs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbs  = new TH1F("EffPTbs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAbs  = new TH1F("EffETAbs","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbt = new TH1F("EffNVTXbt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbt  = new TH1F("EffPTbt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAbt  = new TH1F("EffETAbt","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbc = new TH1F("EffNVTXbc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbc  = new TH1F("EffPTbc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAbc  = new TH1F("EffETAbc","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbn = new TH1F("EffNVTXbn","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbn  = new TH1F("EffPTbn","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAbn  = new TH1F("EffETAbn","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXbp = new TH1F("EffNVTXbp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTbp  = new TH1F("EffPTbp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAbp  = new TH1F("EffETAbp","Signal Eff vs PT T s",100,-5,5);

  //PT
  TH1F *EffPTMs  = new TH1F("EffPTMs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTMt  = new TH1F("EffPTMt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTMc  = new TH1F("EffPTMc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTMp  = new TH1F("EffPTMp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTMn  = new TH1F("EffPTMn","Signal Eff vs PT T s",100,0,800);


  TH1F *EffPTTs  = new TH1F("EffPTTs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTTt  = new TH1F("EffPTTt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTTc  = new TH1F("EffPTTc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTTp  = new TH1F("EffPTTp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffPTTn  = new TH1F("EffPTTn","Signal Eff vs PT T s",100,0,800);

  //NVTX
  TH1F *EffNVTXMs  = new TH1F("EffNVTXMs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMt  = new TH1F("EffNVTXMt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMc  = new TH1F("EffNVTXMc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMp  = new TH1F("EffNVTXMp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXMn  = new TH1F("EffNVTXMn","Signal Eff vs NVTX T s",100,0,100);


  TH1F *EffNVTXTs  = new TH1F("EffNVTXTs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTt  = new TH1F("EffNVTXTt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTc  = new TH1F("EffNVTXTc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTp  = new TH1F("EffNVTXTp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffNVTXTn  = new TH1F("EffNVTXTn","Signal Eff vs NVTX T s",100,0,100);

  //ETA
  TH1F *EffETAMs  = new TH1F("EffETAMs","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMt  = new TH1F("EffETAMt","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMc  = new TH1F("EffETAMc","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMp  = new TH1F("EffETAMp","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETAMn  = new TH1F("EffETAMn","Signal Eff vs ETA T s",100,-5,5);


  TH1F *EffETATs  = new TH1F("EffETATs","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATt  = new TH1F("EffETATt","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATc  = new TH1F("EffETATc","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATp  = new TH1F("EffETATp","Signal Eff vs ETA T s",100,-5,5);
  TH1F *EffETATn  = new TH1F("EffETATn","Signal Eff vs ETA T s",100,-5,5);


  //Medium 
  TH1F *EffNVTXMbs = new TH1F("EffNVTXMbs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbs  = new TH1F("EffPTMbs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAMbs  = new TH1F("EffETAMbs","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbt = new TH1F("EffNVTXMbt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbt  = new TH1F("EffPTMbt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAMbt  = new TH1F("EffETAMbt","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbc = new TH1F("EffNVTXMbc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbc  = new TH1F("EffPTMbc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAMbc  = new TH1F("EffETAMbc","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbn = new TH1F("EffNVTXMbn","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbn  = new TH1F("EffPTMbn","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAMbn  = new TH1F("EffETAMbn","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXMbp = new TH1F("EffNVTXMbp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTMbp  = new TH1F("EffPTMbp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETAMbp  = new TH1F("EffETAMbp","Signal Eff vs PT T s",100,-5,5);

  //Tight 
  TH1F *EffNVTXTbs = new TH1F("EffNVTXTbs","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbs  = new TH1F("EffPTTbs","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETATbs  = new TH1F("EffETATbs","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbt = new TH1F("EffNVTXTbt","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbt  = new TH1F("EffPTTbt","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETATbt  = new TH1F("EffETATbt","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbc = new TH1F("EffNVTXTbc","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbc  = new TH1F("EffPTTbc","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETATbc  = new TH1F("EffETATbc","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbn = new TH1F("EffNVTXTbn","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbn  = new TH1F("EffPTTbn","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETATbn  = new TH1F("EffETATbn","Signal Eff vs PT T s",100,-5,5);

  TH1F *EffNVTXTbp = new TH1F("EffNVTXTbp","Signal Eff vs NVTX T s",100,0,100);
  TH1F *EffPTTbp  = new TH1F("EffPTTbp","Signal Eff vs PT T s",100,0,800);
  TH1F *EffETATbp  = new TH1F("EffETATbp","Signal Eff vs PT T s",100,-5,5);





  
  //Setting the Tree Branches

  //TFile *finput = new TFile( "/uscms_data/d3/asroy/PhotonIdTuning/CMSSW_7_3_5/src/CutBasedPhoID2016/merged/AllPV/PF/Trainner/CutTMVABarrel90.root");
  //TFile *finput = new TFile( "/uscms_data/d3/asroy/PhotonIdTuning/CMSSW_7_3_5/src/CutBasedPhoID2016/merged/TruePV/PF/Trainner/CutTMVABarrel90.root");    
  TFile *finput = new TFile( "/uscms_data/d3/asroy/PhotonIdTuning/CMSSW_7_3_5/src/CutBasedPhoID2016/merged/AllPV/PF/Isopt/CutTMVABarrel90_HPT.root"); 

  float Ppt,Peta,Pphi,isoP,isoC,isoN,sieie,toe,weight;
  int   nvtx; 
  
  //  weight = 1.0; 

  finput->cd();
  //Signal Tree                                                                 
  t_S->SetBranchAddress("Sieie",&sieie);
  t_S->SetBranchAddress("isoP",&isoP);
  t_S->SetBranchAddress("isoC",&isoC);
  t_S->SetBranchAddress("isoN",&isoN);
  t_S->SetBranchAddress("ToE",&toe);
  t_S->SetBranchAddress("weighT",&weight);
  t_S->SetBranchAddress("Nvtx",&nvtx);
  t_S->SetBranchAddress("Peta",&Peta);
  t_S->SetBranchAddress("Ppt",&Ppt);

  //Background Tree                                                                 
  t_B->SetBranchAddress("Sieie",&sieie);
  t_B->SetBranchAddress("isoP",&isoP);
  t_B->SetBranchAddress("isoC",&isoC);
  t_B->SetBranchAddress("isoN",&isoN);
  t_B->SetBranchAddress("ToE",&toe);
  t_B->SetBranchAddress("weighT",&weight);
  t_B->SetBranchAddress("Nvtx",&nvtx);
  t_B->SetBranchAddress("Peta",&Peta);
  t_B->SetBranchAddress("Ppt",&Ppt);


  
  EffNVTX0->Sumw2();
  EffPT0->Sumw2();
  EffETA0->Sumw2();
  EffPHI0->Sumw2();
  
  EffNVTXL->Sumw2();
  EffPTL->Sumw2();
  EffETAL->Sumw2();
  EffPHIL->Sumw2();
  
  EffNVTXM->Sumw2();
  EffPTM->Sumw2();
  EffETAM->Sumw2();
  EffPHIM->Sumw2();
  
  EffNVTXT->Sumw2();
  EffPTT->Sumw2();
  EffETAT->Sumw2();
  EffPHIT->Sumw2();
  
  
  EffNVTX0b->Sumw2();
  EffPT0b->Sumw2();
  EffETA0b->Sumw2();
  EffPHI0b->Sumw2();
  
  EffNVTXLb->Sumw2();
  EffPTLb->Sumw2();
  EffETALb->Sumw2();
  EffPHILb->Sumw2();
  
  EffNVTXMb->Sumw2();
  EffPTMb->Sumw2();
  EffETAMb->Sumw2();
  EffPHIMb->Sumw2();
  
  EffNVTXTb->Sumw2();
  EffPTTb->Sumw2();
  EffETATb->Sumw2();
  EffPHITb->Sumw2(); 

  
  EffNVTXs->Sumw2();
  EffPTs->Sumw2();
  EffETAs->Sumw2();
  
  EffNVTXt->Sumw2();
  EffPTt->Sumw2();
  EffETAt->Sumw2();
  
  EffNVTXc->Sumw2();
  EffPTc->Sumw2();
  EffETAc->Sumw2();
  
  EffNVTXn->Sumw2();
  EffPTn->Sumw2();
  EffETAn->Sumw2();

  EffNVTXp->Sumw2();
  EffPTp->Sumw2();
  EffETAp->Sumw2();

  
  EffNVTXbs->Sumw2();
  EffPTbs->Sumw2();
  EffETAbs->Sumw2();

  EffNVTXbt->Sumw2();
  EffPTbt->Sumw2();
  EffETAbt->Sumw2();

  EffNVTXbc->Sumw2();
  EffPTbc->Sumw2();
  EffETAbc->Sumw2();

  EffNVTXbn->Sumw2();
  EffPTbn->Sumw2();
  EffETAbn->Sumw2();

  EffNVTXbp->Sumw2();
  EffPTbp->Sumw2();
  EffETAbp->Sumw2();

  //PT    
  EffPTMs->Sumw2();
  EffPTMt->Sumw2();
  EffPTMc->Sumw2();
  EffPTMp->Sumw2();
  EffPTMn->Sumw2();
    
  EffPTTs->Sumw2();
  EffPTTt->Sumw2();
  EffPTTc->Sumw2();
  EffPTTp->Sumw2();
  EffPTTn->Sumw2();

  //NVTX
  EffNVTXMs->Sumw2();
  EffNVTXMt->Sumw2();
  EffNVTXMc->Sumw2();
  EffNVTXMp->Sumw2();
  EffNVTXMn->Sumw2();
    
  EffNVTXTs->Sumw2();
  EffNVTXTt->Sumw2();
  EffNVTXTc->Sumw2();
  EffNVTXTp->Sumw2();
  EffNVTXTn->Sumw2();

  //ETA
  EffETAMs->Sumw2();
  EffETAMt->Sumw2();
  EffETAMc->Sumw2();
  EffETAMp->Sumw2();
  EffETAMn->Sumw2();
    
  EffETATs->Sumw2();
  EffETATt->Sumw2();
  EffETATc->Sumw2();
  EffETATp->Sumw2();
  EffETATn->Sumw2();

  //Medium
  EffNVTXMbs->Sumw2();
  EffPTMbs->Sumw2();
  EffETAMbs->Sumw2();

  EffNVTXMbt->Sumw2();
  EffPTMbt->Sumw2();
  EffETAMbt->Sumw2();

  EffNVTXMbc->Sumw2();
  EffPTMbc->Sumw2();
  EffETAMbc->Sumw2();

  EffNVTXMbn->Sumw2();
  EffPTMbn->Sumw2();
  EffETAMbn->Sumw2();

  EffNVTXMbp->Sumw2();
  EffPTMbp->Sumw2();
  EffETAMbp->Sumw2();

  //Tight
  EffNVTXTbs->Sumw2();
  EffPTTbs->Sumw2();
  EffETATbs->Sumw2();

  EffNVTXTbt->Sumw2();
  EffPTTbt->Sumw2();
  EffETATbt->Sumw2();

  EffNVTXTbc->Sumw2();
  EffPTTbc->Sumw2();
  EffETATbc->Sumw2();

  EffNVTXTbn->Sumw2();
  EffPTTbn->Sumw2();
  EffETATbn->Sumw2();

  EffNVTXTbp->Sumw2();
  EffPTTbp->Sumw2();
  EffETATbp->Sumw2();


  for(int i = 0; i < t_S->GetEntries(); i++){
    t_S->GetEntry(i);
    
    EffNVTX0->Fill(nvtx,weight);
    EffPT0->Fill(Ppt,weight);
    EffETA0->Fill(Peta,weight);

  
    //Loose Cut: 
    if((sieie  < sieL)&&
       (toe    < 0.05)&&
       (isoP-0.0047*Ppt < isoPL)&&
       (isoC   < isoCL)&&
       (isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNL)){
      
      EffNVTXL->Fill(nvtx,weight);
      EffPTL->Fill(Ppt,weight);
      EffETAL->Fill(Peta,weight);
    }
    
    //Medium Cut:
    if((sieie  < sieM)&&
       (toe    < 0.05)&&
       (isoP -0.0047*Ppt < isoPM)&&
       (isoC   < isoCM)&&
       (isoN- (0.0148*Ppt+0.000017*Ppt*Ppt) < isoNM)){
      EffNVTXM->Fill(nvtx,weight);
      EffPTM->Fill(Ppt,weight);
      EffETAM->Fill(Peta,weight);
    }
    //Tight Cut:
    if((sieie  < sieT)&&
       (toe    < 0.05)&&
       (isoP -0.0047*Ppt < isoPT)&&
       (isoC   < isoCT)&&
       (isoN - (0.0148*Ppt+0.000017*Ppt*Ppt) < isoNT)){
      EffNVTXT->Fill(nvtx,weight);
      EffPTT->Fill(Ppt,weight);
      EffETAT->Fill(Peta,weight);
    }
    //Branch out Cuts
    if(sieie  < sieL){
       EffNVTXs->Fill(nvtx,weight);
       EffPTs->Fill(Ppt,weight);
       EffETAs->Fill(Peta,weight);
       
    }
    if(toe    < 0.05){
      EffNVTXt->Fill(nvtx,weight);
      EffPTt->Fill(Ppt,weight);
      EffETAt->Fill(Peta,weight);
     
    }    
    if(isoP -0.0047*Ppt < isoPL){    
      EffNVTXp->Fill(nvtx,weight);
      EffPTp->Fill(Ppt,weight);
      EffETAp->Fill(Peta,weight);
     
    }    
    if(isoC   < isoCL){
      EffNVTXc->Fill(nvtx,weight);
      EffPTc->Fill(Ppt,weight);
      EffETAc->Fill(Peta,weight);
     
    }
    if(isoN-(0.0148*Ppt + 0.000017*Ppt*Ppt) < isoNL){
      EffNVTXn->Fill(nvtx,weight);
      EffPTn->Fill(Ppt,weight);
      EffETAn->Fill(Peta,weight);
     
    }

    //Branch out Cuts Medium
    if(sieie  < sieM){
       EffPTMs->Fill(Ppt,weight);
       EffNVTXMs->Fill(nvtx,weight);
       EffETAMs->Fill(Peta,weight);
    }
    if(toe    < 0.05){
      EffPTMt->Fill(Ppt,weight);
      EffNVTXMt->Fill(nvtx,weight);
      EffETAMt->Fill(Peta,weight);
    }    
    if(isoP -0.0047*Ppt < isoPM){    
      EffPTMp->Fill(Ppt,weight);
      EffNVTXMp->Fill(nvtx,weight);
      EffETAMp->Fill(Peta,weight);
    }    
    if(isoC   < isoCM){
      EffPTMc->Fill(Ppt,weight);
      EffNVTXMc->Fill(nvtx,weight);
      EffETAMc->Fill(Peta,weight);
    }
    if(isoN-(0.0148*Ppt + 0.000017*Ppt*Ppt) < isoNM){
      EffPTMn->Fill(Ppt,weight);
      EffNVTXMn->Fill(nvtx,weight);
      EffETAMn->Fill(Peta,weight);
    }

    //Branch out Cuts Tight
    if(sieie  < sieT){
       EffPTTs->Fill(Ppt,weight);
       EffNVTXTs->Fill(nvtx,weight);
       EffETATs->Fill(Peta,weight);
    }
    if(toe    < 0.05){
      EffPTTt->Fill(Ppt,weight);
      EffNVTXTt->Fill(nvtx,weight);
      EffETATt->Fill(Peta,weight);
    }    
    if(isoP -0.0047*Ppt < isoPT){    
      EffPTTp->Fill(Ppt,weight);
      EffNVTXTp->Fill(nvtx,weight);
      EffETATp->Fill(Peta,weight);
    }    
    if(isoC   < isoCT){
      EffPTTc->Fill(Ppt,weight);
      EffNVTXTc->Fill(nvtx,weight);
      EffETATc->Fill(Peta,weight);
    }
    if(isoN-(0.0148*Ppt + 0.000017*Ppt*Ppt) < isoNT){
      EffPTTn->Fill(Ppt,weight);
      EffNVTXTn->Fill(nvtx,weight);
      EffETATn->Fill(Peta,weight);
    }





  }  


  //plots for Background 


  for(int i = 0; i < t_B->GetEntries(); i++){
    t_B->GetEntry(i);
    EffNVTX0b->Fill(nvtx,weight);
    EffPT0b->Fill(Ppt,weight);
    EffETA0b->Fill(Peta,weight);
  
    //Loose Cut: 
    if((sieie  < sieL)&&
       (toe    < 0.05)&&
       (isoP -0.0047*Ppt < isoPL)&&
       (isoC   < isoCL)&&
       (isoN-((0.0148*Ppt+0.000017*Ppt*Ppt)) < isoNL)){
      
      EffNVTXLb->Fill(nvtx,weight);
      EffPTLb->Fill(Ppt,weight);
      EffETALb->Fill(Peta,weight);
    }
    
    //Medium Cut:
    if((sieie  < sieM)&&
       (toe    < 0.05)&&
       (isoP -0.0047*Ppt < isoPM)&&
       (isoC   < isoCM)&&
       (isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNM)){
      EffNVTXMb->Fill(nvtx,weight);
      EffPTMb->Fill(Ppt,weight);
      EffETAMb->Fill(Peta,weight);
    }
    //Tight Cut:
    if((sieie  < sieT)&&
       (toe    < 0.05)&&
       (isoP -0.0047*Ppt < isoPT)&&
       (isoC   < isoCT)&&
       (isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNT)){
      EffNVTXTb->Fill(nvtx,weight);
      EffPTTb->Fill(Ppt,weight);
      EffETATb->Fill(Peta,weight);
    }
    //Branch out Cuts
    //Loose
    if(sieie  < sieL){
       EffNVTXbs->Fill(nvtx,weight);
       EffPTbs->Fill(Ppt,weight);
       EffETAbs->Fill(Peta,weight);
    }
    if(toe    < 0.05){
      EffNVTXbt->Fill(nvtx,weight);
      EffPTbt->Fill(Ppt,weight);
      EffETAbt->Fill(Peta,weight);
    }    
    if(isoP -0.0047*Ppt < isoPL){    
      EffNVTXbp->Fill(nvtx,weight);
      EffPTbp->Fill(Ppt,weight);
      EffETAbp->Fill(Peta,weight);
     }    
    if(isoC   < isoCL){
      EffNVTXbc->Fill(nvtx,weight);
      EffPTbc->Fill(Ppt,weight);
      EffETAbc->Fill(Peta,weight);
 
    }
    if(isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNL){
      EffNVTXbn->Fill(nvtx,weight);
      EffPTbn->Fill(Ppt,weight);
      EffETAbn->Fill(Peta,weight);
      
    }

    //Medium
    if(sieie  < sieM){
       EffNVTXMbs->Fill(nvtx,weight);
       EffPTMbs->Fill(Ppt,weight);
       EffETAMbs->Fill(Peta,weight);
    }
    if(toe    < 0.05){
      EffNVTXMbt->Fill(nvtx,weight);
      EffPTMbt->Fill(Ppt,weight);
      EffETAMbt->Fill(Peta,weight);
    }    
    if(isoP -0.0047*Ppt < isoPM){    
      EffNVTXMbp->Fill(nvtx,weight);
      EffPTMbp->Fill(Ppt,weight);
      EffETAMbp->Fill(Peta,weight);
     }    
    if(isoC   < isoCM){
      EffNVTXMbc->Fill(nvtx,weight);
      EffPTMbc->Fill(Ppt,weight);
      EffETAMbc->Fill(Peta,weight);
 
    }
    if(isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNM){
      EffNVTXMbn->Fill(nvtx,weight);
      EffPTMbn->Fill(Ppt,weight);
      EffETAMbn->Fill(Peta,weight);
      
    }


    //Tight
    if(sieie  < sieT){
       EffNVTXTbs->Fill(nvtx,weight);
       EffPTTbs->Fill(Ppt,weight);
       EffETATbs->Fill(Peta,weight);
    }
    if(toe    < 0.05){
      EffNVTXTbt->Fill(nvtx,weight);
      EffPTTbt->Fill(Ppt,weight);
      EffETATbt->Fill(Peta,weight);
    }    
    if(isoP -0.0047*Ppt < isoPT){    
      EffNVTXTbp->Fill(nvtx,weight);
      EffPTTbp->Fill(Ppt,weight);
      EffETATbp->Fill(Peta,weight);
     }    
    if(isoC   < isoCT){
      EffNVTXTbc->Fill(nvtx,weight);
      EffPTTbc->Fill(Ppt,weight);
      EffETATbc->Fill(Peta,weight);
 
    }
    if(isoN-(0.0148*Ppt+0.000017*Ppt*Ppt) < isoNT){
      EffNVTXTbn->Fill(nvtx,weight);
      EffPTTbn->Fill(Ppt,weight);
      EffETATbn->Fill(Peta,weight);
      
    }

  }



  TFile *f1 = new TFile("Eff1.root","recreate");
  f1->cd();
  EffNVTX0->Write();
  EffPT0->Write();
  EffETA0->Write();
  EffPHI0->Write();
  
  EffNVTXL->Write();
  EffPTL->Write();
  EffETAL->Write();
  EffPHIL->Write();
  
  EffNVTXM->Write();
  EffPTM->Write();
  EffETAM->Write();
  EffPHIM->Write();
  
  EffNVTXT->Write();
  EffPTT->Write();
  EffETAT->Write();
  EffPHIT->Write();


  EffNVTX0b->Write();
  EffPT0b->Write();
  EffETA0b->Write();
  EffPHI0b->Write();
  
  EffNVTXLb->Write();
  EffPTLb->Write();
  EffETALb->Write();
  EffPHILb->Write();
  
  EffNVTXMb->Write();
  EffPTMb->Write();
  EffETAMb->Write();
  EffPHIMb->Write();
  
  EffNVTXTb->Write();
  EffPTTb->Write();
  EffETATb->Write();
  EffPHITb->Write(); 


  EffNVTXs->Write();
  EffPTs->Write();
  EffETAs->Write();


  EffNVTXt->Write();
  EffPTt->Write();
  EffETAt->Write();
    
  EffNVTXc->Write();
  EffPTc->Write();
  EffETAc->Write();


  EffNVTXn->Write();
  EffPTn->Write();
  EffETAn->Write();
  

  EffNVTXp->Write();
  EffPTp->Write();
  EffETAp->Write();

  
  EffNVTXbs->Write();
  EffPTbs->Write();
  EffETAbs->Write();

  
  EffNVTXbt->Write();
  EffPTbt->Write();
  EffETAbt->Write();
  
  EffNVTXbc->Write();
  EffPTbc->Write();
  EffETAbc->Write();

  EffNVTXbn->Write();
  EffPTbn->Write();
  EffETAbn->Write();

  EffNVTXbp->Write();
  EffPTbp->Write(); 
  EffETAbp->Write();


  //PT
  EffPTMs->Write();
  EffPTMt->Write();
  EffPTMc->Write();
  EffPTMp->Write();
  EffPTMn->Write();
    
  EffPTTs->Write();
  EffPTTt->Write();
  EffPTTc->Write();
  EffPTTp->Write();
  EffPTTn->Write();

  //NVTX
  EffNVTXMs->Write();
  EffNVTXMt->Write();
  EffNVTXMc->Write();
  EffNVTXMp->Write();
  EffNVTXMn->Write();
    
  EffNVTXTs->Write();
  EffNVTXTt->Write();
  EffNVTXTc->Write();
  EffNVTXTp->Write();
  EffNVTXTn->Write();

  //ETA
  EffETAMs->Write();
  EffETAMt->Write();
  EffETAMc->Write();
  EffETAMp->Write();
  EffETAMn->Write();
    
  EffETATs->Write();
  EffETATt->Write();
  EffETATc->Write();
  EffETATp->Write();
  EffETATn->Write();
  
  //Medium
  EffNVTXMbs->Write();
  EffPTMbs->Write();
  EffETAMbs->Write();
  
  EffNVTXMbt->Write();
  EffPTMbt->Write();
  EffETAMbt->Write();
  
  EffNVTXMbc->Write();
  EffPTMbc->Write();
  EffETAMbc->Write();

  EffNVTXMbn->Write();
  EffPTMbn->Write();
  EffETAMbn->Write();

  EffNVTXMbp->Write();
  EffPTMbp->Write(); 
  EffETAMbp->Write();

  //Tight
  EffNVTXTbs->Write();
  EffPTTbs->Write();
  EffETATbs->Write();
  
  EffNVTXTbt->Write();
  EffPTTbt->Write();
  EffETATbt->Write();
  
  EffNVTXTbc->Write();
  EffPTTbc->Write();
  EffETATbc->Write();

  EffNVTXTbn->Write();
  EffPTTbn->Write();
  EffETATbn->Write();

  EffNVTXTbp->Write();
  EffPTTbp->Write(); 
  EffETATbp->Write();




  TFile *feta = new TFile("Eff1etaB.root","recreate");
  feta->cd();


  EffETA0->Write();
  EffETA0b->Write();


  EffETAs->Write();
  EffETAt->Write();
  EffETAc->Write();
  EffETAn->Write();
  EffETAp->Write();


  EffETAbs->Write();
  EffETAbt->Write();
  EffETAbc->Write();
  EffETAbn->Write();
  EffETAbp->Write();

 




}

