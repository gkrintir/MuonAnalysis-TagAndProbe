#ifndef tnp_weight_h
#define tnp_weight_h

#include "TMath.h"

// IN THIS FILE YOU WILL FIND:
// ++++++++++++++

// - TrkM: 
//	(tnp_weight_trkM_ppb) // NEEDS TO BE UPDATED
//   * idx = 0:  nominal
//   * idx = 1..100: toy variations, stat. only
//   * idx = -1: syst variation, "new_MAX", +1 sigma NOT YET IMPLEMENTED
//   * idx = -2: syst variation, "new_MAX", -1 sigma NOT YET IMPLEMENTED
//   * idx = -10: binned

// - MuID: 
//	(tnp_weight_muid_ppb)
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down
//   * idx = -13: binned, syst up
//   * idx = -14: binned, syst down
//
// (tnp_weight_muid_nTrack)  - data correction based on the number of tracks in the event (integrated value = 1). It is for a single muon, for dimuons it would need to be squared
//   * idx = 0: binned, nominal
//   * idx = -11: binned, stat up
//   * idx = -12: binned, stat down

// - Trigger: 
//	(tnp_weight_trg_ppb)
//   * idx = 0: nominal
//   * idx = -11: stat variation,  +1 sigma
//   * idx = -12: stat variation,  -1 sigma
//   * idx = -13: syst variation,  +1 sigma  //TO BE UPDATED
//   * idx = -14: syst variation,  -1 sigma

// THE INDIVIDUAL SFs
// ++++++++++++++++++
double tnp_weight_trkM_ppb(double pt, double eta, int idx = 0); //TO BE UPDATED
double tnp_weight_muid_ppb(double pt, double eta, int idx = 0); // HAS BEEN UPDATED
double tnp_weight_muid_nTrack(int nTrack, int idx = 0); //
double tnp_weight_trg_ppb(double pt, double eta, int idx = 0);



///////////////////////////////////////////////////
//                 T r k M    P P b                //
///////////////////////////////////////////////////
double tnp_weight_trkM_ppb(double pt, double eta, int idx) {
	double x = pt;

	if (idx == 10) {
		if (fabs(eta) < 0.9) {
			// 0 < |eta| < 1.2
			if (pt < 15) return 0.994131;
			else if (pt < 25) return 0.960778;
			else if (pt < 30) return 0.975896;
			else if (pt < 35) return 0.981953;
			else if (pt < 40) return 0.980849;
			else if (pt < 45) return 0.994185;
			else if (pt < 50) return 0.9948;
			else if (pt < 80) return 0.991582;
			else if (pt < 200) return 1.00307;
		}
		else if (fabs(eta) < 2.1) {
			// 1.2 < |eta| < 2.1
			if (pt < 15) return 1.01259;
			else if (pt < 25) return 0.946523;
			else if (pt < 30) return 0.989628;
			else if (pt < 35) return 0.980356;
			else if (pt < 40) return 0.990009;
			else if (pt < 45) return 0.993151;
			else if (pt < 50) return 0.994683;
			else if (pt < 80) return 0.998054;
			else if (pt < 200) return 1.00241;
		}
		else {
			// 2.1 < |eta| < 2.4
			if (pt < 15) return 0.871449;
			else if (pt < 25) return 0.966795;
			else if (pt < 40) return 0.975846;
			else if (pt < 80) return 0.994159;
			else if (pt < 200) return 0.971635;
		}
	}

	double num = 1, den = 1;


	return num / den;
}

///////////////////////////////////////////////////
//               M U I D      P P b              //
///////////////////////////////////////////////////
double tnp_weight_muid_ppb(double pt, double eta, int idx) {
	double x = pt;

	double num = 1.0, den = 0.0;  //intentionaly 0, so if asked for a corrections outside defined range, it returns NaN instead of 1

	// MC
	if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
		if (pt > 3.3 && pt <= 4.5) den = 0.980292;
		else if (pt <= 5.5) den = 0.988652;
		else if (pt <= 6.5) den = 0.991186;
		else if (pt <= 8) den = 0.99211;
		else if (pt <= 10.5) den = 0.993282;
		else if (pt <= 14) den = 0.993677;
		else if (pt <= 18) den = 0.993716;
		else if (pt < 9999) den = 0.989668;
	}
	else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
		if (pt > 1.1 && pt <= 3.3) den = 0.972175;
		else if (pt <= 4.5) den = 0.986112;
		else if (pt <= 5.5) den = 0.989617;
		else if (pt <= 6.5) den = 0.992082;
		else if (pt <= 8) den = 0.993391;
		else if (pt <= 10.5) den = 0.993456;
		else if (pt <= 14) den = 0.996085;
		else if (pt <= 18) den = 0.994577;
		else if (pt < 9999) den = 0.994608;
	}
	else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
		if (pt > 0.8 && pt <= 2) den = 0.973474;
		else if (pt <= 3.5) den = 0.994106;
		else if (pt <= 4.5) den = 0.997574;
		else if (pt <= 6.5) den = 0.99761;
		else if (pt <= 10) den = 0.998036;
		else if (pt <= 14) den = 0.997462;
		else if (pt < 9999) den = 0.997858;
	}
	else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
		if (pt > 0.8 && pt <= 2) den = 0.975377;
		else if (pt <= 3.5) den = 0.992559;
		else if (pt <= 5.5) den = 0.994019;
		else if (pt <= 12) den = 0.995517;
		else if (pt < 9999) den = 1;
	}

	// data
	if (idx == 0) { // nominal
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978123;
			else if (pt <= 5.5) num = 0.985305;
			else if (pt <= 6.5) num = 0.98696;
			else if (pt <= 8) num = 0.98821;
			else if (pt <= 10.5) num = 0.989972;
			else if (pt <= 14) num = 0.991429;
			else if (pt <= 18) num = 0.990797;
			else if (pt < 9999) num = 0.991848;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.973117;
			else if (pt <= 4.5) num = 0.984226;
			else if (pt <= 5.5) num = 0.988538;
			else if (pt <= 6.5) num = 0.991459;
			else if (pt <= 8) num = 0.991702;
			else if (pt <= 10.5) num = 0.990132;
			else if (pt <= 14) num = 0.992181;
			else if (pt <= 18) num = 0.992159;
			else if (pt < 9999) num = 0.992774;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.944705;
			else if (pt <= 3.5) num = 0.977526;
			else if (pt <= 4.5) num = 1;
			else if (pt <= 6.5) num = 0.99665;
			else if (pt <= 10) num = 1;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.942625;
			else if (pt <= 3.5) num = 0.979907;
			else if (pt <= 5.5) num = 0.987211;
			else if (pt <= 12) num = 0.997746;
			else if (pt < 9999) num = 0.999999;
		}
	}
	else if (idx == -11) { // stat up
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978818;
			else if (pt <= 5.5) num = 0.986103;
			else if (pt <= 6.5) num = 0.987913;
			else if (pt <= 8) num = 0.989186;
			else if (pt <= 10.5) num = 0.991042;
			else if (pt <= 14) num = 0.992865;
			else if (pt <= 18) num = 0.993177;
			else if (pt < 9999) num = 0.995012;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.976812;
			else if (pt <= 4.5) num = 0.985077;
			else if (pt <= 5.5) num = 0.989537;
			else if (pt <= 6.5) num = 0.99261;
			else if (pt <= 8) num = 0.992858;
			else if (pt <= 10.5) num = 0.991484;
			else if (pt <= 14) num = 0.993958;
			else if (pt <= 18) num = 0.995099;
			else if (pt < 9999) num = 0.997159;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.951165;
			else if (pt <= 3.5) num = 0.982042;
			else if (pt <= 4.5) num = 1.00035;
			else if (pt <= 6.5) num = 1;
			else if (pt <= 10) num = 1;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.952285;
			else if (pt <= 3.5) num = 0.988946;
			else if (pt <= 5.5) num = 0.995206;
			else if (pt <= 12) num = 1;
			else if (pt < 9999) num = 1.01117;
		}
	}
	else if (idx == -12) { // stat down
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.977419;
			else if (pt <= 5.5) num = 0.984489;
			else if (pt <= 6.5) num = 0.985978;
			else if (pt <= 8) num = 0.987201;
			else if (pt <= 10.5) num = 0.988857;
			else if (pt <= 14) num = 0.989906;
			else if (pt <= 18) num = 0.988245;
			else if (pt < 9999) num = 0.988349;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.96944;
			else if (pt <= 4.5) num = 0.983372;
			else if (pt <= 5.5) num = 0.987528;
			else if (pt <= 6.5) num = 0.99028;
			else if (pt <= 8) num = 0.990514;
			else if (pt <= 10.5) num = 0.988733;
			else if (pt <= 14) num = 0.990321;
			else if (pt <= 18) num = 0.988999;
			else if (pt < 9999) num = 0.987986;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.938956;
			else if (pt <= 3.5) num = 0.97301;
			else if (pt <= 4.5) num = 0.999653;
			else if (pt <= 6.5) num = 0.992216;
			else if (pt <= 10) num = 0.997602;
			else if (pt <= 14) num = 0.99683;
			else if (pt < 9999) num = 0.996159;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.930772;
			else if (pt <= 3.5) num = 0.971151;
			else if (pt <= 5.5) num = 0.979352;
			else if (pt <= 12) num = 0.9896;
			else if (pt < 9999) num = 0.988826;
		}
	}
	if (idx == -13) { // TnP fit syst up
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.978613;
			else if (pt <= 5.5) num = 0.985822;
			else if (pt <= 6.5) num = 0.987338;
			else if (pt <= 8) num = 0.988535;
			else if (pt <= 10.5) num = 0.990339;
			else if (pt <= 14) num = 0.991878;
			else if (pt <= 18) num = 0.991286;
			else if (pt < 9999) num = 0.992211;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.98176;
			else if (pt <= 4.5) num = 0.985291;
			else if (pt <= 5.5) num = 0.98949;
			else if (pt <= 6.5) num = 0.992347;
			else if (pt <= 8) num = 0.992573;
			else if (pt <= 10.5) num = 0.99101;
			else if (pt <= 14) num = 0.993075;
			else if (pt <= 18) num = 0.993063;
			else if (pt < 9999) num = 0.993638;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.949066;
			else if (pt <= 3.5) num = 0.979764;
			else if (pt <= 4.5) num = 1.0019;
			else if (pt <= 6.5) num = 0.99765;
			else if (pt <= 10) num = 1.00022;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.964941;
			else if (pt <= 3.5) num = 0.985622;
			else if (pt <= 5.5) num = 0.99152;
			else if (pt <= 12) num = 1.00001;
			else if (pt < 9999) num = 1.00055;
		}
	}
	else if (idx == -14) { // TnP fit syst down
		if (fabs(eta) > 0 && fabs(eta) <= 0.8) {
			if (pt > 3.3 && pt <= 4.5) num = 0.977633;
			else if (pt <= 5.5) num = 0.984787;
			else if (pt <= 6.5) num = 0.986582;
			else if (pt <= 8) num = 0.987885;
			else if (pt <= 10.5) num = 0.989604;
			else if (pt <= 14) num = 0.99098;
			else if (pt <= 18) num = 0.990308;
			else if (pt < 9999) num = 0.991485;
		}
		else if (fabs(eta) > 0.8 && fabs(eta) <= 1.5) {
			if (pt > 1.1 && pt <= 3.3) num = 0.964475;
			else if (pt <= 4.5) num = 0.98316;
			else if (pt <= 5.5) num = 0.987586;
			else if (pt <= 6.5) num = 0.990572;
			else if (pt <= 8) num = 0.99083;
			else if (pt <= 10.5) num = 0.989254;
			else if (pt <= 14) num = 0.991287;
			else if (pt <= 18) num = 0.991256;
			else if (pt < 9999) num = 0.991909;
		}
		else if (fabs(eta) > 1.5 && fabs(eta) <= 2.1) {
			if (pt > 0.8 && pt <= 2) num = 0.940343;
			else if (pt <= 3.5) num = 0.975288;
			else if (pt <= 4.5) num = 0.998101;
			else if (pt <= 6.5) num = 0.99565;
			else if (pt <= 10) num = 0.999779;
			else if (pt <= 14) num = 1;
			else if (pt < 9999) num = 1;
		}
		else if (fabs(eta) > 2.1 && fabs(eta) <= 2.4) {
			if (pt > 0.8 && pt <= 2) num = 0.920309;
			else if (pt <= 3.5) num = 0.974193;
			else if (pt <= 5.5) num = 0.982901;
			else if (pt <= 12) num = 0.995479;
			else if (pt < 9999) num = 0.999448;
		}
	}
	return (num / den);
}

////////////////// N   T R A C K    ///////////////

double tnp_weight_muid_nTrack(int nTrack, int idx)
{
	if (idx == 0) {
		if (nTrack <= 35) return 1.00907;
		else if (nTrack <= 60) return 1.00433;
		else if (nTrack <= 90) return 0.999192;
		else if (nTrack <= 120) return 0.999982;
		else if (nTrack <= 155) return 0.996984;
		else if (nTrack <= 190) return 0.987001;
		else return 1.00127;
	}
	if (idx == -11) {
		if (nTrack <= 35) return 1.01043;
		else if (nTrack <= 60) return 1.00533;
		else if (nTrack <= 90) return 1.00028;
		else if (nTrack <= 120) return 1.00201;
		else if (nTrack <= 155) return 1.00084;
		else if (nTrack <= 190) return 0.995623;
		else return 1.02132;
	}
	if (idx == -12) {
		if (nTrack <= 35) return 1.00773;
		else if (nTrack <= 60) return 1.00332;
		else if (nTrack <= 90) return 0.99811;
		else if (nTrack <= 120) return 0.997972;
		else if (nTrack <= 155) return 0.99318;
		else if (nTrack <= 190) return 0.978575;
		else return 0.981994;
	}
	return -1; //default return for bad idx
}



///////////////////////////////////////////////////
//                 T R G    P P b                //
///////////////////////////////////////////////////


double tnp_weight_trg_ppb(double pt, double eta, int idx)
{
	//
	// nominal
	//
	if (idx == 0)
	{
		if (fabs(eta) < 0.9) {
			// 0 < |eta| < 0.9
			if (pt < 3.8) return 1.01005;
			else if (pt < 4.5) return 1.00015;
			else if (pt < 5.5) return 1.00859;
			else if (pt < 6.5) return 0.994886;
			else if (pt < 8) return 0.979021;
			else if (pt < 10.5) return 0.978756;
			else if (pt < 14) return 0.973643;
			else if (pt < 18) return 0.96243;
			else if (pt < 9999) return 0.954136;
		}

		else if (fabs(eta) < 1.2) {
			// 0.9 < |eta| < 1.2
			if (pt < 3.8) return 1.25081;
			else if (pt < 4.5) return 1.03099;
			else if (pt < 5.5) return 1.00102;
			else if (pt < 6.5) return 0.999884;
			else if (pt < 8) return 0.998999;
			else if (pt < 10.5) return 0.99726;
			else if (pt < 14) return 1.00131;
			else if (pt < 18) return 0.999727;
			else if (pt < 9999) return 0.98394;
		}

		else if (fabs(eta) < 1.6) {
			// 1.2 < |eta| < 1.6
			if (pt < 3) return 1.22981;
			else if (pt < 4.5) return 1.03105;
			else if (pt < 6.5) return 1.0091;
			else if (pt < 10) return 1.00626;
			else if (pt < 14) return 1.00334;
			else if (pt < 9999) return 1.01464;
		}

		else if (fabs(eta) < 2.1) {
			// 1.6 < |eta| < 2.1
			if (pt < 2.2) return 1.11018;
			else if (pt < 3) return 1.02508;
			else if (pt < 4.5) return 0.990083;
			else if (pt < 6.5) return 0.987711;
			else if (pt < 10) return 0.979898;
			else if (pt < 14) return 0.985277;
			else if (pt < 9999) return 0.994803;
		}

		else {
			// 2.1 < |eta| < 2.4
			if (pt < 2.2) return 1.13768;
			else if (pt < 3.5) return 1.01454;
			else if (pt < 5.5) return 1.01467;
			else if (pt < 8) return 1.0195;
			else if (pt < 12) return 1.02563;
			else if (pt < 9999) return 1.01239;
		}
	}

	//
	// stat variation; +1 sigma
	//
	if (idx == -11) {
		if (fabs(eta) < 0.9) {
			// 0 < |eta| < 0.9
			if (pt < 3.8) return 1.01483;
			else if (pt < 4.5) return 1.00249;
			else if (pt < 5.5) return 1.01012;
			else if (pt < 6.5) return 0.996521;
			else if (pt < 8) return 0.98077;
			else if (pt < 10.5) return 0.980747;
			else if (pt < 14) return 0.976601;
			else if (pt < 18) return 0.967516;
			else if (pt < 9999) return 0.961453;
		}

		if (fabs(eta) < 1.2) {
			// 0.9 < |eta| < 1.2
			if (pt < 3.8) return 1.25709;
			else if (pt < 4.5) return 1.03244;
			else if (pt < 5.5) return 1.00193;
			else if (pt < 6.5) return 1.00081;
			else if (pt < 8) return 0.999922;
			else if (pt < 10.5) return 0.998407;
			else if (pt < 14) return 1.00283;
			else if (pt < 18) return 1.00312;
			else if (pt < 9999) return 0.994154;
		}

		if (fabs(eta) < 1.6) {
			// 1.2 < |eta| < 1.6
			if (pt < 3) return 1.23642;
			else if (pt < 4.5) return 1.03311;
			else if (pt < 6.5) return 1.01042;
			else if (pt < 10) return 1.00781;
			else if (pt < 14) return 1.00603;
			else if (pt < 9999) return 1.01855;
		}


		if (fabs(eta) < 2.1) {
			// 1.6 < |eta| < 2.1
			if (pt < 2.2) return 1.11552;
			else if (pt < 3) return 1.02766;
			else if (pt < 4.5) return 0.991703;
			else if (pt < 6.5) return 0.989796;
			else if (pt < 10) return 0.982867;
			else if (pt < 14) return 0.991577;
			else if (pt < 9999) return 1.00484;
		}

		else {
			// 2.1 < |eta| < 2.4
			if (pt < 2.2) return 1.14182;
			else if (pt < 3.5) return 1.08768;
			else if (pt < 5.5) return 1.01662;
			else if (pt < 8) return 1.02257;
			else if (pt < 12) return 1.03055;
			else if (pt < 9999) return 1.02306;
		}
	}


	//
	// stat variation; -1 sigma
	//
	if (idx == -12) {
		if (fabs(eta) < 0.9) {
			// 0 < |eta| < 0.9
			if (pt < 3.8) return 1.00521;
			else if (pt < 4.5) return 0.997785;
			else if (pt < 5.5) return 1.00706;
			else if (pt < 6.5) return 0.993219;
			else if (pt < 8) return 0.977251;
			else if (pt < 10.5) return 0.976702;
			else if (pt < 14) return 0.970625;
			else if (pt < 18) return 0.957196;
			else if (pt < 9999) return 0.946546;
		}

		if (fabs(eta) < 1.2) {
			// 0.9 < |eta| < 1.2
			if (pt < 3.8) return 1.24449;
			else if (pt < 4.5) return 1.0295;
			else if (pt < 5.5) return 1.00011;
			else if (pt < 6.5) return 0.998877;
			else if (pt < 8) return 0.99799;
			else if (pt < 10.5) return 0.995996;
			else if (pt < 14) return 0.999574;
			else if (pt < 18) return 0.995765;
			else if (pt < 9999) return 0.976418;
		}

		if (fabs(eta) < 1.6) {
			// 1.2 < |eta| < 1.6
			if (pt < 3) return 1.22322;
			else if (pt < 4.5) return 1.029;
			else if (pt < 6.5) return 1.00777;
			else if (pt < 10) return 1.00467;
			else if (pt < 14) return 1.00049;
			else if (pt < 9999) return 1.01042;
		}

		if (fabs(eta) < 2.1) {
			// 1.6 < |eta| < 2.1
			if (pt < 2.2) return 1.10483;
			else if (pt < 3) return 1.02249;
			else if (pt < 4.5) return 0.988453;
			else if (pt < 6.5) return 0.985607;
			else if (pt < 10) return 0.976892;
			else if (pt < 14) return 0.978845;
			else if (pt < 9999) return 0.984486;
		}

		else {
			// 2.1 < |eta| < 2.4
			if (pt < 2.2) return 1.13354;
			else if (pt < 3.5) return 1.01262;
			else if (pt < 5.5) return 1.01268;
			else if (pt < 8) return 1.01633;
			else if (pt < 12) return 1.02048;
			else if (pt < 9999) return 1.00124;
		}
	}
}


#endif //#ifndef tnp_weight_h
