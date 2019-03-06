//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  6 10:01:30 2019 by ROOT version 6.08/06
// from TTree tree/tree
// found on file: bc_jpsi_mu_nu_gen.root
//////////////////////////////////////////////////////////

#ifndef mass_test_h
#define mass_test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>


class mass_test : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Float_t> run = {fReader, "run"};
   TTreeReaderValue<Float_t> lumi = {fReader, "lumi"};
   TTreeReaderValue<Float_t> event = {fReader, "event"};
   TTreeReaderValue<Float_t> bc_pt = {fReader, "bc_pt"};
   TTreeReaderValue<Float_t> bc_eta = {fReader, "bc_eta"};
   TTreeReaderValue<Float_t> bc_phi = {fReader, "bc_phi"};
   TTreeReaderValue<Float_t> bc_charge = {fReader, "bc_charge"};
   TTreeReaderValue<Float_t> bc_mass = {fReader, "bc_mass"};
   TTreeReaderValue<Float_t> mu_pt = {fReader, "mu_pt"};
   TTreeReaderValue<Float_t> mu_eta = {fReader, "mu_eta"};
   TTreeReaderValue<Float_t> mu_phi = {fReader, "mu_phi"};
   TTreeReaderValue<Float_t> mu_charge = {fReader, "mu_charge"};
   TTreeReaderValue<Float_t> nu_pt = {fReader, "nu_pt"};
   TTreeReaderValue<Float_t> nu_eta = {fReader, "nu_eta"};
   TTreeReaderValue<Float_t> nu_phi = {fReader, "nu_phi"};
   TTreeReaderValue<Float_t> jpsi_pt = {fReader, "jpsi_pt"};
   TTreeReaderValue<Float_t> jpsi_eta = {fReader, "jpsi_eta"};
   TTreeReaderValue<Float_t> jpsi_phi = {fReader, "jpsi_phi"};


   mass_test(TTree * /*tree*/ =0) { }
   virtual ~mass_test() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(mass_test,0);

   // destination file
   TFile *file = new TFile("masses.root","RECREATE");

   // TTree
   TNtuple *complete_Fstate = new TNtuple("complete_final_state","complete_final_state","final_state_mass:mass_diff");
   TNtuple *nuless_Fstate = new TNtuple("nuless_final_state","nuless_final_state","nuless_final_mass:nuless_mass_diff");

   // watch to control the running time of the program
   TStopwatch watch;

   // vectors we use for the analysis
   TLorentzVector Bc, mu, nu, jpsi;
   TLorentzVector final_state;
   TLorentzVector nuless_final_state;

   // set known masses of the particles
   double Bc_mass = 6.2749; //[GeV]
   double mu_mass = 0.1056583745; //[GeV]
   double nu_mass = 0;
   double jpsi_mass = 3.096900; //[GeV]

   // histograms
   TH1F *final_state_mass = new TH1F("J/#psi#mu#nu_{#mu} invariant mass","J/#psi#mu#nu_{#mu} invariant mass",100,6.276,6.279);
   TH1F *mass_diff = new TH1F("J/#psi#mu#nu_{#mu} - B_{c} mass","J/#psi#mu#nu_{#mu} - B_{c} mass",50,-18.5,8);
   TH1F *nuless_mass = new TH1F("J/#psi#mu invariant mass","J/#psi#mu invariant mass",50,3.3,6.3);
   TH1F *nuless_mass_diff = new TH1F("J/#psi#mu - B_{c} mass","J/#psi#mu - B_{c} mass",50,-19,6.5);

   // canvas
   TCanvas *c1 = new TCanvas("Complete final state","Complete final state",1400,700);
   TCanvas *c2 = new TCanvas("Neutrinoless final state","Neutrinoless final state",1400,700);

};

#endif

#ifdef mass_test_cxx
void mass_test::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t mass_test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef mass_test_cxx
