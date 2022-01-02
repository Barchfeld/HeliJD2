// HeliJD2.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//


#include <boost/asio.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "VarStar.h"
#include "jd.h"

using namespace std;
namespace pt = boost::property_tree;
namespace po = boost::program_options;

std::string getGCVSPage(std::string const& star) {
    // http://www.sai.msu.su/gcvs/cgi-bin/search.cgi?search=v456+sgr
    boost::asio::ip::tcp::iostream stream;

    stream.connect("www.sai.msu.su", "http");
    stream << "GET /gcvs/cgi-bin/search.cgi?search=" << star << " HTTP/1.1\r\n";
    stream << "Host: www.sai.msu.su\r\n";
    stream << "Cache-Control: no-cache\r\n";
    stream << "Connection: close\r\n\r\n" << std::flush;

    std::ostringstream os;
    os << stream.rdbuf();
    return os.str();
}

std::string getCDSPage(std::string const& star) {
    // http://cdsweb.u-strasbg.fr/cgi-bin/nph-sesame/-oIxp/?v456+sgr
    boost::asio::ip::tcp::iostream stream;

    stream.connect("cdsweb.u-strasbg.fr", "http");
    stream << "GET /cgi-bin/nph-sesame/-oIxp/?" << star << " HTTP/1.1\r\n";
    stream << "Host: cdsweb.u-strasbg.fr\r\n";
    stream << "Cache-Control: no-cache\r\n";
    stream << "Connection: close\r\n\r\n" << std::flush;

    std::ostringstream os;
    os << stream.rdbuf();
    return os.str();
}


VarStar createVarStarfromCDSXML(std::string const& cdsXmlString) {
    VarStar currStar;
    pt::ptree tree;
    std::stringstream debugxml{ "<Resolver name=\"Sc=Simbad (CDS, via client/server)\"><!--delay: 99ms [2] -->\n"
                                "    <oid>2394746</oid>\n"
                                "    <otype>RR*</otype>\n"
                                "    <jpos>18:49:20.43 -32:55:48.3</jpos>\n"
                                "    <jradeg>282.33514243</jradeg>\n"
                                "    <jdedeg>-32.93009788</jdedeg>\n"
                                "    <refPos>2018yCat.1345....0G</refPos>\n"
                                "    <errRAmas>0.0337</errRAmas><errDEmas>0.0321</errDEmas>\n"
                                "    <pm>\n"
                                "      <v>1.942</v><e>0.086</e><q>A</q><r>2018yCat.1345....0G</r>\n"
                                "      <pa>327</pa>\n"
                                "      <pmRA>-1.060</pmRA><epmRA>0.064</epmRA>\n"
                                "      <pmDE>1.627</pmDE><epmDE>0.058</epmDE>\n"
                                "    </pm>\n"
                                "    <plx><v>0.1549</v><e>0.0341</e><q>A</q><r>2018yCat.1345....0G</r></plx>\n"
                                "    <oname>V* V456 Sgr</oname>\n"
                                "    <alias>2MASS J18492042-3255483</alias>\n"
                                "    <alias>TIC 275740585</alias>\n"
                                "    <alias>V* V456 Sgr</alias>\n"
                                "    <alias>Gaia DR2 6736019625220082816</alias>\n"
                                "    <nrefs>3</nrefs>\n"
                                "  </Resolver>\n"
    };


    // Abschneiden der ersten Bytes, da aus Kommunikation und kein XML
    std::size_t found = cdsXmlString.find("<Resolver");
    std::size_t foundEnd = cdsXmlString.find("</Target");
    std::size_t len = cdsXmlString.length();
    std::string tmp = cdsXmlString.substr(found, foundEnd - found);
    // Debug:
    std::cout << "#####" << std::endl << tmp << std::endl << "#####" << std::endl;

    std::stringstream ss;
    ss << tmp;

    pt::read_xml(ss, tree);
    //pt::read_xml(debugxml,tree);
    currStar.setCoordStr(tree.get<std::string>("Resolver.jpos"));
    currStar.setDeclDeg(tree.get<long double>("Resolver.jdedeg"));
    currStar.setRectDeg(tree.get<long double>("Resolver.jradeg"));
    currStar.setOName(tree.get<std::string>("Resolver.oname"));
    currStar.setOType(tree.get<std::string>("Resolver.otype"));

    return currStar;
}


std::string getVSXPage(std::string const& star) {
    // https://www.aavso.org/vsx/index.php?view=api.object&minfields&ident=V456+sgr
    boost::asio::ip::tcp::iostream stream;

    stream.connect("www.aavso.org", "http");
    stream << "GET /vsx/index.php?view=api.object&minfields&ident=" << star << " HTTP/1.1\r\n";
    stream << "Host: www.aavso.org\r\n";
    stream << "Cache-Control: no-cache\r\n";
    stream << "Connection: close\r\n\r\n" << std::flush;

    std::ostringstream os;
    os << stream.rdbuf();
    return os.str();
}

std::string getGCVSStarLine(std::string starPage) {
    std::string empty{};
    std::vector<std::string> starPageLines;

    boost::split(starPageLines, starPage, [](char c) {return c == '\n'; });

    int i{ 0 };
    long patternCount{ 0 };
    for (std::string line : starPageLines) {
        patternCount = std::count(line.begin(), line.end(), '|');
        // patternCount could be 0, 1, or 21
        // line with 21 is the line with star data
        if (patternCount > 10) {
            return line;
        }
    }
    return empty;
}



int main(int argc, char** argv) {

    // fuer GCVS: Namen wie in http://www.sai.msu.su/gcvs/gcvs/name.txt beschrieben
    std::string star{ "bet+lyr" };
    std::string observationDateTime{ "2022-02-28T23:43:00" }; // ISO 8601:2000

    po::options_description desc
    ("Aufruf : <program> --star <'star name'> --timestamp <'UTC iso 8601 timestamp'>\n", 80);

    desc.add_options()
    ("star", po::value<std::string>()->required(), 
        "star name, i.e. alpha Ori")
    ("timestamp", po::value<std::string>()->required(), 
        "observation timestamp, UTC, ISO 8601, i.e. 2022-02-28T23:43:00");

    boost::program_options::variables_map vm;
    try {
        po::store(po::command_line_parser(argc, argv).
            options(desc).
            run(), vm);
        po::notify(vm);
    }
    catch (po::error& e) {
        std::cout << "ERROR: " << e.what() << "\n";
        std::cout << desc << "\n";
        return 1;
    }

    star = vm["star"].as<std::string>();


    //
    std::string starPage{};
    starPage = getCDSPage(star);
    //std::cout << starPage << std::endl;

    VarStar varStar = createVarStarfromCDSXML(starPage);

    long double jdutc = jd(observationDateTime);


    std::cout << "Berechnung Heliozentrisches JD" << std::endl;
    std::cout << "==============================" << std::endl;
    std::cout.precision(5);
    std::cout << "Searched             : " << star << std::endl;
    std::cout << "Found (CDS Strasbg.) : " << varStar.getOName() << std::endl;
    std::cout << "Coordinates          : " << varStar.getCoordStr() << std::endl;
    std::cout << "Type (CDS)           : " << varStar.getOType() << std::endl;
    std::cout << "ObservationDate (UTC): " << observationDateTime << std::endl;
    std::cout << "JD (UTC)             : " << std::fixed << jdutc << std::endl;

    /*
        starPage = getGCVSPage(star);
        std::string starLine{};
        starLine = getGCVSStarLine(starPage);
        std::cout << starLine << std::endl;
    */

    return 0;
}






// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"

// Tipps für den Einstieg: 
//   1. Verwenden Sie das Projektmappen-Explorer-Fenster zum Hinzufügen/Verwalten von Dateien.
//   2. Verwenden Sie das Team Explorer-Fenster zum Herstellen einer Verbindung mit der Quellcodeverwaltung.
//   3. Verwenden Sie das Ausgabefenster, um die Buildausgabe und andere Nachrichten anzuzeigen.
//   4. Verwenden Sie das Fenster "Fehlerliste", um Fehler anzuzeigen.
//   5. Wechseln Sie zu "Projekt" > "Neues Element hinzufügen", um neue Codedateien zu erstellen, bzw. zu "Projekt" > "Vorhandenes Element hinzufügen", um dem Projekt vorhandene Codedateien hinzuzufügen.
//   6. Um dieses Projekt später erneut zu öffnen, wechseln Sie zu "Datei" > "Öffnen" > "Projekt", und wählen Sie die SLN-Datei aus.
