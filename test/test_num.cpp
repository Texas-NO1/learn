#include <bits/stdc++.h>

double cos(const std::vector<double> &f1, const std::vector<double> &f2) {
    double res = 0;
    for (int i = 0; i < f1.size(); ++i) res += f1.at(i) * f2.at(i);
    return 1 - res;
}

int main () {
    std::vector<double> python_st = {0.09025824815034866, -0.1341097205877304, 0.10439260303974152, 0.2039099782705307, -0.006384212989360094, -0.014931758865714073, 0.11103479564189911, -0.03808094561100006, -0.20523764193058014, -0.024288924410939217, 0.06746207922697067, 0.059024009853601456, -0.19029463827610016, 0.03744949400424957, -0.12087374925613403, 0.1020529642701149, -0.06508244574069977, 0.026777001097798347, -0.06893190741539001, -0.16659922897815704, 0.17140765488147736, 0.07394709438085556, -0.12342369556427002, 0.05786309763789177, -0.18091662228107452, -0.06746859103441238, -0.11724241822957993, 0.04972798377275467, -0.06726111471652985, 0.009268567897379398, -0.05490032956004143, -0.09427022933959961, 0.053856879472732544, 0.03019866533577442, -0.1087086945772171, 0.034604817628860474, 0.05228976905345917, -0.008289116434752941, 0.07488086819648743, -0.013443768955767155, 0.03120267018675804, -0.04652858152985573, 0.00387330143712461, -0.05452793464064598, 0.07902108877897263, -0.08936729282140732, 0.05795919895172119, -0.07987860590219498, -0.17604872584342957, -0.06209144741296768, 0.07414404302835464, -0.12984031438827515, 0.04956468567252159, -0.08275575935840607, 0.10233933478593826, 0.17399613559246063, 0.04545203223824501, 0.03098272532224655, 0.060868389904499054, -0.05328004062175751, -0.11147606372833252, 0.10872364789247513, -0.027774939313530922, -0.18543894588947296, 0.10964520275592804, 0.0037304346915334463, 0.000818783650174737, -0.04782085120677948, 0.016598135232925415, -0.08369798213243484, -0.035147227346897125, -0.1102505549788475, 0.05906221270561218, -0.05105673149228096, -0.017363086342811584, 0.07607042789459229, -0.09599551558494568, 0.10073603689670563, -0.03963257744908333, -0.0180527251213789, 0.19736580550670624, 0.06653887778520584, -0.05331389233469963, -0.05834592133760452, 0.07818269729614258, -0.05919510871171951, 0.11614272743463516, 0.0819888785481453, 0.12632811069488525, -0.010204392485320568, 0.1026456207036972, 0.05484872683882713, -0.017846491187810898, -0.012680742889642715, 0.17093630135059357, -0.017712272703647614, 0.05029592663049698, 0.010875444859266281, -0.03698141500353813, 0.05036691948771477, 0.027162138372659683, 0.06917775422334671, 0.019209375604987144, -0.025412844493985176, -0.1621445119380951, 0.04853019490838051, -0.18125401437282562, -0.15858706831932068, -0.08696822077035904, -0.02927524968981743, 0.05968471243977547, -0.008597114123404026, 0.005037370137870312, 0.011159948073327541, 0.0763339176774025, -0.1231808140873909, 0.04910235479474068, 0.16659477353096008, -0.0013430892722681165, -0.05035863816738129, 0.03804025799036026, 0.04160997271537781, -0.016856729984283447, 0.011206035502254963, 0.10458268970251083, 0.08100984990596771, 0.06367674469947815, 0.054812461137771606}; 
    std::vector<double> python_et = {0.07630942761898041, -0.1342238485813141, 0.1169787347316742, 0.19627618789672852, -0.008645853959023952, 0.03209656476974487, 0.10089980065822601, 0.03296400606632233, -0.20092058181762695, -0.07658175379037857, 0.00032620958518236876, 0.0025817689020186663, -0.2400411069393158, 0.002317243255674839, -0.12563519179821014, 0.1531563103199005, -0.07770958542823792, 0.010714114643633366, -0.06523320823907852, -0.17203852534294128, 0.17429526150226593, 0.04889775067567825, -0.10017305612564087, 0.06449034810066223, -0.07633741199970245, -0.08720133453607559, -0.13194870948791504, 0.034983012825250626, -0.07596077024936676, 0.029475320130586624, -0.03627564013004303, -0.08997980505228043, 0.042089711874723434, 0.013497699052095413, -0.13145920634269714, 0.016776414588093758, 0.045549459755420685, 0.009167933836579323, 0.07616079598665237, -0.034650374203920364, -0.01675708405673504, -0.05656065791845322, 0.0241854228079319, -0.04956109821796417, 0.08670812845230103, -0.05436007305979729, 0.043812453746795654, -0.104921355843544, -0.14893828332424164, -0.05632120370864868, 0.035037796944379807, -0.1371760219335556, 0.015175954438745975, -0.03403918817639351, 0.11784520000219345, 0.20280809700489044, 0.049187857657670975, 0.036430440843105316, 0.08018703758716583, -0.04836444556713104, -0.08790697902441025, 0.09080374240875244, -0.05132546275854111, -0.18751554191112518, 0.0877961665391922, 0.02801358699798584, 0.010847970843315125, -0.052178412675857544, 0.011834784410893917, -0.09115219116210938, -0.024422599002718925, -0.10538795590400696, 0.08083581924438477, -0.06835028529167175, -0.018925782293081284, 0.09718923270702362, -0.08740875124931335, 0.07883599400520325, -0.06107291206717491, -0.015381011180579662, 0.18968097865581512, 0.05875064432621002, -0.06395763158798218, -0.05630401894450188, 0.10426025092601776, -0.07623813301324844, 0.12194934487342834, 0.0636340007185936, 0.11633943021297455, -0.0027609732933342457, 0.09209126234054565, 0.06883055716753006, -0.041226062923669815, -0.02991124801337719, 0.17691220343112946, -0.0013621869729831815, 0.008213487453758717, 0.009699446149170399, -0.06558511406183243, 0.05096811428666115, 0.04179245978593826, 0.052733391523361206, 0.04246542230248451, -0.01896592415869236, -0.15416152775287628, 0.06047707423567772, -0.1617916226387024, -0.16702471673488617, -0.08210251480340958, -0.029334459453821182, 0.06951896846294403, 0.01643976755440235, 0.011860332451760769, 0.008289816789329052, 0.08516314625740051, -0.13650408387184143, 0.05196893960237503, 0.16134381294250488, -0.02872505784034729, -0.05137772113084793, 0.018949609249830246, 0.05070064589381218, -0.007650337181985378, -0.00013810969539918005, 0.10792918503284454, 0.0718565285205841, 0.061415642499923706, 0.060092825442552567};
    std::vector<double> c_st = {0.0464707,-0.115827,0.0502874,0.257319,0.0112941,-0.0033799,0.0930653,-0.0550004,-0.132577,-0.0213482,0.0550312,0.0481725,-0.182864,0.0182974,-0.132721,0.11567,-0.0418274,0.00726789,-0.0607814,-0.156944,0.207451,0.0423089,-0.140531,0.017925,-0.157903,-0.0663613,-0.146575,0.0726063,-0.0936303,0.011669,-0.077607,-0.102861,0.0469858,0.0101596,-0.0358259,0.0322888,0.0824042,-0.00750644,0.0708851,0.00996991,0.0265825,-0.102519,-0.017552,-0.0880548,0.0588485,-0.0619462,0.0559554,-0.0994315,-0.165719,-0.0583991,0.0877572,-0.136626,0.0266664,-0.060377,0.106344,0.213128,0.0690352,0.0507185,0.0587722,-0.0462646,-0.106248,0.126799,-0.0681851,-0.178075,0.114262,0.01878,-0.0280339,-0.0266263,0.0548797,-0.100895,-0.0188134,-0.110895,0.0717548,-0.0386617,0.0181117,0.0875175,-0.0930212,0.117245,-0.0649956,-0.0293827,0.17386,0.0575994,-0.0217817,-0.0649414,0.106203,-0.116116,0.113098,0.0460742,0.0950356,-0.012152,0.0945841,0.0417677,-0.0287586,0.00420866,0.131728,-0.00645361,0.0443283,-0.0141155,-0.0682895,0.0470517,0.00459939,0.0799821,0.00170658,-0.053949,-0.15893,0.0185332,-0.175675,-0.154566,-0.085351,-0.0226237,0.0630671,-0.0315725,0.0190851,0.0100244,0.0803108,-0.11666,0.0377559,0.158793,-0.00333278,-0.0747237,0.033422,0.0402783,-0.00775783,0.0048953,0.113729,0.0654464,0.0451423,0.0516368};
    std::vector<double> c_et = {0.0763094,-0.134224,0.116979,0.196276,-0.00864585,0.0320966,0.1009,0.032964,-0.200921,-0.0765818,0.00032621,0.00258177,-0.240041,0.00231724,-0.125635,0.153156,-0.0777096,0.0107141,-0.0652332,-0.172039,0.174295,0.0488978,-0.100173,0.0644903,-0.0763374,-0.0872013,-0.131949,0.034983,-0.0759608,0.0294753,-0.0362756,-0.0899798,0.0420897,0.0134977,-0.131459,0.0167764,0.0455495,0.00916793,0.0761608,-0.0346504,-0.0167571,-0.0565607,0.0241854,-0.0495611,0.0867081,-0.0543601,0.0438125,-0.104921,-0.148938,-0.0563212,0.0350378,-0.137176,0.015176,-0.0340392,0.117845,0.202808,0.0491879,0.0364304,0.080187,-0.0483644,-0.087907,0.0908037,-0.0513255,-0.187516,0.0877962,0.0280136,0.010848,-0.0521784,0.0118348,-0.0911522,-0.0244226,-0.105388,0.0808358,-0.0683503,-0.0189258,0.0971892,-0.0874088,0.078836,-0.0610729,-0.015381,0.189681,0.0587506,-0.0639576,-0.056304,0.10426,-0.0762381,0.121949,0.063634,0.116339,-0.00276097,0.0920913,0.0688306,-0.0412261,-0.0299112,0.176912,-0.00136219,0.00821349,0.00969945,-0.0655851,0.0509681,0.0417925,0.0527334,0.0424654,-0.0189659,-0.154162,0.0604771,-0.161792,-0.167025,-0.0821025,-0.0293345,0.069519,0.0164398,0.0118603,0.00828982,0.0851631,-0.136504,0.0519689,0.161344,-0.0287251,-0.0513777,0.0189496,0.0507006,-0.00765034,-0.00013811,0.107929,0.0718565,0.0614156,0.0600928};
    std::cout << python_st.size() << std::endl;
    assert(python_st.size() == python_et.size() );
    assert(c_st.size() == c_et.size());
    assert(python_et.size() == c_st.size());
    std::cout << "python " << cos(python_st, python_et) << std::endl;
    std::cout << "c++ " << cos(c_st, c_et) << std::endl;
    std::cout << "st self " << cos(python_st, c_st) << std::endl;
    std::cout << "et self " << cos(python_et, c_et) << std::endl;
    return 0;
}