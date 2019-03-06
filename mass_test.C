#define mass_test_cxx
// The class definition in mass_test.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("mass_test.C")
// root> T->Process("mass_test.C","some options")
// root> T->Process("mass_test.C+")
//


#include "mass_test.h"
#include <TH2.h>
#include <TStyle.h>

void mass_test::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

   // start the running time control watch
   watch.Start();

   final_state_mass->SetXTitle("Invariant mass [GeV/c^{2}]");
   nuless_mass->SetXTitle("Invariant mass [GeV/c^{2}]");
   mass_diff->SetXTitle("Invariant mass difference [GeV/c^{2}]");
   nuless_mass_diff->SetXTitle("Invariant mass difference [GeV/c^{2}]");
}

void mass_test::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t mass_test::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   fReader.SetEntry(entry);


   // set the TLorentzVectors
   Bc.SetPtEtaPhiM(*bc_pt,*bc_eta,*bc_phi,*bc_mass);
   mu.SetPtEtaPhiM(*mu_pt,*mu_eta,*mu_phi,mu_mass);
   nu.SetPtEtaPhiM(*nu_pt,*nu_eta,*nu_phi,nu_mass);
   jpsi.SetPtEtaPhiM(*jpsi_pt,*jpsi_eta,*jpsi_phi,jpsi_mass);
   // calculate final state TLorentzVectors
   final_state = nu + mu + jpsi;
   nuless_final_state = mu + jpsi;

   final_state_mass->Fill(final_state.M());
   nuless_mass->Fill(nuless_final_state.M());
   mass_diff->Fill(final_state.M() - *bc_mass);
   nuless_mass_diff->Fill(nuless_final_state.M() - *bc_mass);

   complete_Fstate->Fill(final_state.M(),final_state.M() - *bc_mass);
   nuless_Fstate->Fill(nuless_final_state.M(),nuless_final_state.M() - *bc_mass);

   return kTRUE;
}

void mass_test::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void mass_test::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   //gStyle->SetOptStat(0);
   //gStyle->SetOptFit(1111);

   //  write on file
   file->Write();

   // draw everything
   c1->Divide(2,1);
   c1->cd(1);
   final_state_mass->Draw();
   c1->cd(2);
   mass_diff->Draw();
   c1->Print("complete_final_state.png");

   c2->Divide(2,1);
   c2->cd(1);
   nuless_mass->Draw();
   c2->cd(2);
   nuless_mass_diff->Draw();
   c2->Print("nuless_final_state.png");

   // stop the watch and print running time
   cout << "Running time: " <<  watch.RealTime() << endl;

}
