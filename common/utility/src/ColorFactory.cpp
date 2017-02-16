/**
MIT License

Copyright (c) 2016 cbtek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
#include "ColorFactory.h"
#include "Random.h"
#include "StringUtils.hpp"


using namespace cbtek::common::utility;

namespace cbtek {
namespace common {
namespace utility {

common::utility::Random m_colorRng;

inline static size_t binToInt(const std::string &binary, bool ltr)
{

    unsigned long int value = 0;
    for(std::uint32_t a1 = 0;a1<binary.size();a1++)
    {
        char token = (ltr?binary[a1]:binary[(binary.size()-1)-a1]);
        if (token =='1')
        {
            value+= static_cast<unsigned long>(std::pow(2.0,static_cast<int>(a1)));
        }
    }
    return value;
}

inline static int hexToInt(const std::string &hex, bool ltr=false)
{
        std::map<char,std::string> binaryMap;
        binaryMap['0']="0000";
        binaryMap['1']="0001";
        binaryMap['2']="0010";
        binaryMap['3']="0011";
        binaryMap['4']="0100";
        binaryMap['5']="0101";
        binaryMap['6']="0110";
        binaryMap['7']="0111";
        binaryMap['8']="1000";
        binaryMap['9']="1001";
        binaryMap['a']="1010";
        binaryMap['b']="1011";
        binaryMap['c']="1100";
        binaryMap['d']="1101";
        binaryMap['e']="1110";
        binaryMap['f']="1111";
        binaryMap['A']="1010";
        binaryMap['B']="1011";
        binaryMap['C']="1100";
        binaryMap['D']="1101";
        binaryMap['E']="1110";
        binaryMap['F']="1111";

        std::string binary="";
        for (std::uint32_t a1 = 0;a1<hex.size();a1++)
        {
            binary+= binaryMap[hex[a1]];
        }
        return binToInt(binary,ltr);
}
inline static std::string hexToIntString(const std::string &hex)
{
    std::string value;
    for (std::uint32_t a1 = 0;a1<hex.size();a1++)
    {
        if (hex[a1]!=' ')
        {
            value.push_back(hex[a1]);
        }
    }
        std::ostringstream out;
    for (std::uint32_t a1=1;a1<value.size();a1+=2)
    {
        std::string byte;
        byte.push_back(value[a1-1]);
        byte.push_back(value[a1]);
        out << hexToInt(byte)<<" ";
    }
    return out.str();

}
namespace colors{

static ColorType NEXT_COLOR = colors::ColorType(0);
}

Color ColorFactory::create(const std::string & rgba)
{
    Color color;
    uint8_t red=0,green=0,blue=0,alpha=255;
    std::string colorStr=StringUtils::toLowerTrimmed(rgba);

    if (colorStr.size()>0)
    {
        if (colorStr[0]=='#')
        {
            colorStr.erase(colorStr.begin()+0);
        }

        std::string redStr="00",greenStr="00",blueStr="00",alphaStr="ff";
        if (colorStr.size()==3)
        {
            redStr[0]=(colorStr[0]);
            redStr[1]=(colorStr[0]);

            greenStr[0]=(colorStr[1]);
            greenStr[1]=(colorStr[1]);

            blueStr[0]=(colorStr[2]);
            blueStr[1]=(colorStr[2]);

        }
        else if (colorStr.size()==4)
        {
            redStr[0]=(colorStr[0]);
            redStr[1]=(colorStr[0]);

            greenStr[0]=(colorStr[1]);
            greenStr[1]=(colorStr[1]);

            blueStr[0]=(colorStr[2]);
            blueStr[1]=(colorStr[2]);

            alphaStr[0]=(colorStr[3]);
            alphaStr[1]=(colorStr[3]);

        }
        else if (colorStr.size()==6)
        {
            redStr=colorStr.substr(0,2);
            greenStr=colorStr.substr(2,2);
            blueStr=colorStr.substr(4,2);
        }

        else if (colorStr.size()==8)
        {
            redStr=colorStr.substr(0,2);
            greenStr=colorStr.substr(2,2);
            blueStr=colorStr.substr(4,2);
            alphaStr=colorStr.substr(6,2);
        }

        red = StringUtils::toNumber<std::uint32_t>(hexToIntString(redStr));
        green = StringUtils::toNumber<std::uint32_t>(hexToIntString(greenStr));
        blue = StringUtils::toNumber<std::uint32_t>(hexToIntString(blueStr));
        alpha = StringUtils::toNumber<std::uint32_t>(hexToIntString(alphaStr));
    }
    color.set(red,green,blue,alpha);
    return color;
}

Color ColorFactory::create(const colors::ColorType &color)
{
    switch(color)
    {

        case colors::FOREST_GREEN:return Color("Forest Green",0,64,0);break;
        case colors::PURPLE:return Color("Purple",127,0,127);break;
        case colors::PURPLE_GREY:return Color("Purple Grey",127,100,127);break;
        case colors::SHADOW_GREY:return Color("Shadow Grey",64,64,64);break;
        case colors::SEA_FOAM_GREEN:return Color("Sea Foam Green",99,200,64);break;
        case colors::DESERT_MUAVE:return Color("Desert Muave",128,64,64);break;
        case colors::BURNT_OLIVE:return Color("Burnt Olive",64,64,0);break;
        case colors::BURGANDY:return Color("Burgandy",64,0,0);break;
        case colors::OLIVE_DRAB:return Color("Olive Drab",128,128,0);break;
        case colors::MAROON:return Color("Maroon",128,0,0);break;
        case colors::TORQUOISE:return Color("Torquioise",0,128,128);break;
        case colors::WHINE:return Color("Whine",128,0,128);break;
        case colors::BURNT_RED:return Color("Burnt Red",192,0,0);break;
        case colors::GREEN:return Color("Green",0,192,0);break;
        case colors::JADE_BLUE:return Color("Jade Blue",0,192,192);break;
        case colors::ORANGE:return Color("Orange",255,128,0);break;
        case colors::BRIGHT_BLUE:return Color("Bright Blue",0,255,255);break;
        case colors::BRILLIANT_PURPLE:return Color("Brilliant Purple",255,0,255);break;
        case colors::GOLD:return Color("Gold",255,192,128);break;
        case colors::YELLOW_GOLD:return Color("Yellow Gold",255,255,128);break;
        case colors::PALE_SALMON:return Color("Pale Salmon",255,192,192);break;
        case colors::PALE_ORANGE:return Color("Pale Orange",255,224,192);break;
        case colors::PALE_YELLOW:return Color("Pale Yellow",255,255,192);break;
        case colors::PALE_PURPLE:return Color("Pale Purple",192,192,255);break;
        case colors::ACID_GREEN:return Color("Acid green",168,25,187);break;
        case colors::AERO:return Color("Aero",124,185,232);break;
        case colors::AERO_BLUE:return Color("Aero blue",201,255,229);break;
        case colors::AFRICAN_PURPLE:return Color("African purple",178,132,190);break;
        case colors::AIR_FORCE_BLUE_RAF:return Color("Air Force blue (RAF)",93,138,168);break;
        case colors::AIR_FORCE_BLUE_USAF:return Color("Air Force blue (USAF)",0,48,143);break;
        case colors::AIR_SUPERIORITY_BLUE:return Color("Air superiority blue",114,160,193);break;
        case colors::ALABAMA_CRIMSON:return Color("Alabama Crimson",175,0,42);break;
        case colors::ALICE_BLUE:return Color("Alice blue",240,248,255);break;
        case colors::ALIZARIN_CRIMSON:return Color("Alizarin crimson",227,38,54);break;
        case colors::ALLOY_ORANGE:return Color("Alloy orange",196,98,16);break;
        case colors::ALMOND:return Color("Almond",239,222,205);break;
        case colors::AMARANTH:return Color("Amaranth",229,43,80);break;
        case colors::AMARANTH_PINK:return Color("Amaranth pink",241,156,187);break;
        case colors::AMARANTH_PURPLE:return Color("Amaranth purple",171,39,79);break;
        case colors::AMAZON:return Color("Amazon",59,122,87);break;
        case colors::AMBER:return Color("Amber",255,191,0);break;
        case colors::SAE_ECE_AMBER_COLOR:return Color("SAE/ECE Amber (color)",255,126,0);break;
        case colors::AMERICAN_ROSE:return Color("American rose",255,3,62);break;
        case colors::AMETHYST:return Color("Amethyst",153,102,204);break;
        case colors::ANDROID_GREEN:return Color("Android green",164,198,57);break;
        case colors::GUI_BLUE: return Color("Gui Blue",49,106,197);
        case colors::ANTI_FLASH_WHITE:return Color("Anti-flash white",242,243,244);break;
        case colors::ANTIQUE_BRASS:return Color("Antique brass",205,149,117);break;
        case colors::ANTIQUE_BRONZE:return Color("Antique bronze",102,93,30);break;
        case colors::ANTIQUE_FUCHSIA:return Color("Antique fuchsia",145,92,131);break;
        case colors::ANTIQUE_RUBY:return Color("Antique ruby",132,27,45);break;
        case colors::ANTIQUE_WHITE:return Color("Antique white",250,235,215);break;
        case colors::AO_ENGLISH:return Color("Ao (English)",0,128,0);break;
        case colors::APPLE_GREEN:return Color("Apple green",141,182,0);break;
        case colors::APRICOT:return Color("Apricot",251,206,177);break;
        case colors::AQUA:return Color("Aqua",0,255,255);break;
        case colors::AQUAMARINE:return Color("Aquamarine",127,255,212);break;
        case colors::ARMY_GREEN:return Color("Army green",75,83,32);break;
        case colors::ARSENIC:return Color("Arsenic",59,68,75);break;
        case colors::ARTICHOKE:return Color("Artichoke",143,151,121);break;
        case colors::ARYLIDE_YELLOW:return Color("Arylide yellow",233,214,107);break;
        case colors::ASH_GREY:return Color("Ash grey",178,190,181);break;
        case colors::ASPARAGUS:return Color("Asparagus",135,169,107);break;
        case colors::ATOMIC_TANGERINE:return Color("Atomic tangerine",255,153,102);break;
        case colors::AUBURN:return Color("Auburn",165,42,42);break;
        case colors::AUREOLIN:return Color("Aureolin",253,238,0);break;
        case colors::AUROMETALSAURUS:return Color("AuroMetalSaurus",110,127,128);break;
        case colors::AVOCADO:return Color("Avocado",86,130,3);break;
        case colors::AZURE:return Color("Azure",0,127,255);break;
        case colors::AZURE_MIST_WEB:return Color("Azure mist/web",240,255,255);break;
        case colors::BABY_BLUE:return Color("Baby blue",137,207,240);break;
        case colors::BABY_BLUE_EYES:return Color("Baby blue eyes",161,202,241);break;
        case colors::BABY_PINK:return Color("Baby pink",244,194,194);break;
        case colors::BABY_POWDER:return Color("Baby powder",254,254,250);break;
        case colors::BAKER_MILLER_PINK:return Color("Baker-Miller pink",255,145,175);break;
        case colors::BALL_BLUE:return Color("Ball blue",33,171,205);break;
        case colors::BANANA_MANIA:return Color("Banana Mania",250,231,181);break;
        case colors::BANANA_YELLOW:return Color("Banana yellow",255,225,53);break;
        case colors::BANGLADESH_GREEN:return Color("Bangladesh green",0,106,78);break;
        case colors::BARBIE_PINK:return Color("Barbie pink",224,33,138);break;
        case colors::BARN_RED:return Color("Barn red",124,10,2);break;
        case colors::BATTLESHIP_GREY:return Color("Battleship grey",132,132,130);break;
        case colors::BAZAAR:return Color("Bazaar",152,119,123);break;
        case colors::BEAU_BLUE:return Color("Beau blue",188,212,230);break;
        case colors::BEAVER:return Color("Beaver",159,129,112);break;
        case colors::BEIGE:return Color("Beige",245,245,220);break;
        case colors::BDAZZLED_BLUE:return Color("B-dazzled blue",46,88,148);break;
        case colors::BIG_DIP_O_RUBY:return Color("Big-dip-o-ruby",156,37,66);break;
        case colors::BISQUE:return Color("Bisque",255,228,196);break;
        case colors::BISTRE:return Color("Bistre",61,43,31);break;
        case colors::BISTRE_BROWN:return Color("Bistre brown",150,113,23);break;
        case colors::BITTER_LEMON:return Color("Bitter lemon",202,224,13);break;
        case colors::BITTER_LIME:return Color("Bitter lime",100,140,17);break;
        case colors::BITTERSWEET:return Color("Bittersweet",254,111,94);break;
        case colors::BITTERSWEET_SHIMMER:return Color("Bittersweet shimmer",191,79,81);break;
        case colors::BLACK:return Color("Black",0,0,0);break;
        case colors::BLACK_BEAN:return Color("Black bean",61,12,2);break;
        case colors::BLACK_LEATHER_JACKET:return Color("Black leather jacket",37,53,41);break;
        case colors::BLACK_OLIVE:return Color("Black olive",59,60,54);break;
        case colors::BLANCHED_ALMOND:return Color("Blanched almond",255,235,205);break;
        case colors::BLAST_OFF_BRONZE:return Color("Blast-off bronze",165,113,100);break;
        case colors::BLEU_DE_FRANCE:return Color("Bleu de France",49,140,231);break;
        case colors::BLIZZARD_BLUE:return Color("Blizzard Blue",172,229,238);break;
        case colors::BLOND:return Color("Blond",250,240,190);break;
        case colors::BLUE:return Color("Blue",0,0,255);break;
        case colors::BLUE_CRAYOLA:return Color("Blue (Crayola)",31,117,254);break;
        case colors::BLUE_MUNSELL:return Color("Blue (Munsell)",0,147,175);break;
        case colors::BLUE_NCS:return Color("Blue (NCS)",0,135,189);break;
        case colors::BLUE_PIGMENT:return Color("Blue (pigment)",51,51,153);break;
        case colors::BLUE_RYB:return Color("Blue (RYB)",2,71,254);break;
        case colors::BLUE_BELL:return Color("Blue Bell",162,162,208);break;
        case colors::BLUE_GRAY:return Color("Blue-gray",102,153,204);break;
        case colors::BLUE_GREEN:return Color("Blue-green",13,152,186);break;
        case colors::BLUE_SAPPHIRE:return Color("Blue sapphire",18,97,128);break;
        case colors::BLUE_VIOLET:return Color("Blue-violet",138,43,226);break;
        case colors::BLUE_YONDER:return Color("Blue yonder",80,114,167);break;
        case colors::BLUEBERRY:return Color("Blueberry",79,134,247);break;
        case colors::BLUEBONNET:return Color("Bluebonnet",28,28,240);break;
        case colors::BLUSH:return Color("Blush",222,93,131);break;
        case colors::BOLE:return Color("Bole",121,68,59);break;
        case colors::BONDI_BLUE:return Color("Bondi blue",0,149,182);break;
        case colors::BONE:return Color("Bone",227,218,201);break;
        case colors::BOSTON_UNIVERSITY_RED:return Color("Boston University Red",204,0,0);break;
        case colors::BOTTLE_GREEN:return Color("Bottle green",0,106,78);break;
        case colors::BOYSENBERRY:return Color("Boysenberry",135,50,96);break;
        case colors::BRANDEIS_BLUE:return Color("Brandeis blue",0,112,255);break;
        case colors::BRASS:return Color("Brass",181,166,66);break;
        case colors::BRICK_RED:return Color("Brick red",203,65,84);break;
        case colors::BRIGHT_CERULEAN:return Color("Bright cerulean",29,172,214);break;
        case colors::BRIGHT_GREEN:return Color("Bright green",102,255,0);break;
        case colors::BRIGHT_LAVENDER:return Color("Bright lavender",191,148,228);break;
        case colors::BRIGHT_LILAC:return Color("Bright lilac",216,145,239);break;
        case colors::BRIGHT_MAROON:return Color("Bright maroon",195,33,72);break;
        case colors::BRIGHT_NAVY_BLUE:return Color("Bright navy blue",25,116,210);break;
        case colors::BRIGHT_PINK:return Color("Bright pink",255,0,127);break;
        case colors::BRIGHT_TURQUOISE:return Color("Bright turquoise",8,232,222);break;
        case colors::BRIGHT_UBE:return Color("Bright ube",209,159,232);break;
        case colors::BRILLIANT_LAVENDER:return Color("Brilliant lavender",244,187,255);break;
        case colors::BRILLIANT_ROSE:return Color("Brilliant rose",255,85,163);break;
        case colors::BRINK_PINK:return Color("Brink pink",251,96,127);break;
        case colors::BRITISH_RACING_GREEN:return Color("British racing green",0,66,37);break;
        case colors::BRONZE:return Color("Bronze",205,127,50);break;
        case colors::BRONZE_YELLOW:return Color("Bronze Yellow",115,112,0);break;
        case colors::BROWN_TRADITIONAL:return Color("Brown (traditional)",150,75,0);break;
        case colors::BROWN_WEB:return Color("Brown (web)",165,42,42);break;
        case colors::BROWN_NOSE:return Color("Brown-nose",107,68,35);break;
        case colors::BRUNSWICK_GREEN:return Color("Brunswick green",27,77,62);break;
        case colors::BUBBLE_GUM:return Color("Bubble gum",255,193,204);break;
        case colors::BUBBLES:return Color("Bubbles",231,254,255);break;
        case colors::BUFF:return Color("Buff",240,220,130);break;
        case colors::BUD_GREEN:return Color("Bud green",123,182,97);break;
        case colors::BULGARIAN_ROSE:return Color("Bulgarian rose",72,6,7);break;
        case colors::BURGUNDY:return Color("Burgundy",128,0,32);break;
        case colors::BURLYWOOD:return Color("Burlywood",222,184,135);break;
        case colors::BURNT_ORANGE:return Color("Burnt orange",204,85,0);break;
        case colors::BURNT_SIENNA:return Color("Burnt sienna",233,116,81);break;
        case colors::BURNT_UMBER:return Color("Burnt umber",138,51,36);break;
        case colors::BYZANTINE:return Color("Byzantine",189,51,164);break;
        case colors::BYZANTIUM:return Color("Byzantium",112,41,99);break;
        case colors::CADET:return Color("Cadet",83,104,114);break;
        case colors::CADET_BLUE:return Color("Cadet blue",95,158,160);break;
        case colors::CADET_GREY:return Color("Cadet grey",145,163,176);break;
        case colors::CADMIUM_GREEN:return Color("Cadmium green",0,107,60);break;
        case colors::CADMIUM_ORANGE:return Color("Cadmium orange",237,135,45);break;
        case colors::CADMIUM_RED:return Color("Cadmium red",227,0,34);break;
        case colors::CADMIUM_YELLOW:return Color("Cadmium yellow",255,246,0);break;
        case colors::CAFE_AU_LAIT:return Color("Cafe au lait",166,123,91);break;
        case colors::CAFE_NOIR:return Color("Cafe noir",75,54,33);break;
        case colors::CAL_POLY_GREEN:return Color("Cal Poly green",30,77,43);break;
        case colors::CAMBRIDGE_BLUE:return Color("Cambridge Blue",163,193,173);break;
        case colors::CAMEL:return Color("Camel",193,154,107);break;
        case colors::CAMEO_PINK:return Color("Cameo pink",239,187,204);break;
        case colors::CAMOUFLAGE_GREEN:return Color("Camouflage green",120,134,107);break;
        case colors::CANARY_YELLOW:return Color("Canary yellow",255,239,0);break;
        case colors::CANDY_APPLE_RED:return Color("Candy apple red",255,8,0);break;
        case colors::CANDY_PINK:return Color("Candy pink",228,113,122);break;
        case colors::CAPRI:return Color("Capri",0,191,255);break;
        case colors::CAPUT_MORTUUM:return Color("Caput mortuum",89,39,32);break;
        case colors::CARDINAL:return Color("Cardinal",196,30,58);break;
        case colors::CARIBBEAN_GREEN:return Color("Caribbean green",0,204,153);break;
        case colors::CARMINE:return Color("Carmine",150,0,24);break;
        case colors::CARMINE_M_AND_P:return Color("Carmine (M&P)",215,0,64);break;
        case colors::CARMINE_PINK:return Color("Carmine pink",235,76,66);break;
        case colors::CARMINE_RED:return Color("Carmine red",255,0,56);break;
        case colors::CARNATION_PINK:return Color("Carnation pink",255,166,201);break;
        case colors::CARNELIAN:return Color("Carnelian",179,27,27);break;
        case colors::CAROLINA_BLUE:return Color("Carolina blue",153,186,221);break;
        case colors::CARROT_ORANGE:return Color("Carrot orange",237,145,33);break;
        case colors::CASTLETON_GREEN:return Color("Castleton green",0,86,63);break;
        case colors::CATALINA_BLUE:return Color("Catalina blue",6,42,120);break;
        case colors::CATAWBA:return Color("Catawba",112,54,66);break;
        case colors::CEDAR_CHEST:return Color("Cedar Chest",201,90,73);break;
        case colors::CEIL:return Color("Ceil",146,161,207);break;
        case colors::CELADON:return Color("Celadon",172,225,175);break;
        case colors::CELADON_BLUE:return Color("Celadon blue",0,123,167);break;
        case colors::CELADON_GREEN:return Color("Celadon green",47,132,124);break;
        case colors::CELESTE:return Color("Celeste",178,255,255);break;
        case colors::CELESTIAL_BLUE:return Color("Celestial blue",73,151,208);break;
        case colors::CERISE:return Color("Cerise",222,49,99);break;
        case colors::CERISE_PINK:return Color("Cerise pink",236,59,131);break;
        case colors::CERULEAN:return Color("Cerulean",0,123,167);break;
        case colors::CERULEAN_BLUE:return Color("Cerulean blue",42,82,190);break;
        case colors::CERULEAN_FROST:return Color("Cerulean frost",109,155,195);break;
        case colors::CG_BLUE:return Color("CG Blue",0,122,165);break;
        case colors::CG_RED:return Color("CG Red",224,60,49);break;
        case colors::CHAMOISEE:return Color("Chamoisee",160,120,90);break;
        case colors::CHAMPAGNE:return Color("Champagne",247,231,206);break;
        case colors::CHARCOAL:return Color("Charcoal",54,69,79);break;
        case colors::CHARLESTON_GREEN:return Color("Charleston green",35,43,43);break;
        case colors::CHARM_PINK:return Color("Charm pink",230,143,172);break;
        case colors::CHARTREUSE_TRADITIONAL:return Color("Chartreuse (traditional)",223,255,0);break;
        case colors::CHARTREUSE_WEB:return Color("Chartreuse (web)",127,255,0);break;
        case colors::CHERRY:return Color("Cherry",222,49,99);break;
        case colors::CHERRY_BLOSSOM_PINK:return Color("Cherry blossom pink",255,183,197);break;
        case colors::CHESTNUT:return Color("Chestnut",149,69,53);break;
        case colors::CHINA_PINK:return Color("China pink",222,111,161);break;
        case colors::CHINA_ROSE:return Color("China rose",168,81,110);break;
        case colors::CHINESE_RED:return Color("Chinese red",170,56,30);break;
        case colors::CHINESE_VIOLET:return Color("Chinese violet",133,96,136);break;
        case colors::CHOCOLATE_TRADITIONAL:return Color("Chocolate (traditional)",123,63,0);break;
        case colors::CHOCOLATE_WEB:return Color("Chocolate (web)",210,105,30);break;
        case colors::CHROME_YELLOW:return Color("Chrome yellow",255,167,0);break;
        case colors::CINEREOUS:return Color("Cinereous",152,129,123);break;
        case colors::CINNABAR:return Color("Cinnabar",227,66,52);break;
        case colors::CINNAMON:return Color("Cinnamon",210,105,30);break;
        case colors::CITRINE:return Color("Citrine",228,208,10);break;
        case colors::CITRON:return Color("Citron",159,169,31);break;
        case colors::CLARET:return Color("Claret",127,23,52);break;
        case colors::CLASSIC_ROSE:return Color("Classic rose",251,204,231);break;
        case colors::COBALT:return Color("Cobalt",0,71,171);break;
        case colors::COCOA_BROWN:return Color("Cocoa brown",210,105,30);break;
        case colors::COCONUT:return Color("Coconut",150,90,62);break;
        case colors::COFFEE:return Color("Coffee",111,78,55);break;
        case colors::COLUMBIA_BLUE:return Color("Columbia blue",155,221,255);break;
        case colors::CONGO_PINK:return Color("Congo pink",248,131,121);break;
        case colors::COOL_BLACK:return Color("Cool black",0,46,99);break;
        case colors::COOL_GREY:return Color("Cool grey",140,146,172);break;
        case colors::COPPER:return Color("Copper",184,115,51);break;
        case colors::COPPER_CRAYOLA:return Color("Copper (Crayola)",218,138,103);break;
        case colors::COPPER_PENNY:return Color("Copper penny",173,111,105);break;
        case colors::COPPER_RED:return Color("Copper red",203,109,81);break;
        case colors::COPPER_ROSE:return Color("Copper rose",153,102,102);break;
        case colors::COQUELICOT:return Color("Coquelicot",255,56,0);break;
        case colors::CORAL:return Color("Coral",255,127,80);break;
        case colors::CORAL_PINK:return Color("Coral pink",248,131,121);break;
        case colors::CORAL_RED:return Color("Coral red",255,64,64);break;
        case colors::CORDOVAN:return Color("Cordovan",137,63,69);break;
        case colors::CORN:return Color("Corn",251,236,93);break;
        case colors::CORNELL_RED:return Color("Cornell Red",179,27,27);break;
        case colors::CORNFLOWER_BLUE:return Color("Cornflower blue",100,149,237);break;
        case colors::CORNSILK:return Color("Cornsilk",255,248,220);break;
        case colors::COSMIC_LATTE:return Color("Cosmic latte",255,248,231);break;
        case colors::COTTON_CANDY:return Color("Cotton candy",255,188,217);break;
        case colors::CREAM:return Color("Cream",255,253,208);break;
        case colors::CRIMSON:return Color("Crimson",220,20,60);break;
        case colors::CRIMSON_GLORY:return Color("Crimson glory",190,0,50);break;
        case colors::CYAN:return Color("Cyan",0,255,255);break;
        case colors::SUPER_CYAN: return Color ("Super Cyan", 51,204,204);
        case colors::CYAN_PROCESS:return Color("Cyan (process)",0,183,235);break;
        case colors::CYBER_GRAPE:return Color("Cyber grape",88,66,124);break;
        case colors::CYBER_YELLOW:return Color("Cyber yellow",255,211,0);break;
        case colors::DAFFODIL:return Color("Daffodil",255,255,49);break;
        case colors::DANDELION:return Color("Dandelion",240,225,48);break;
        case colors::DARK_BLUE:return Color("Dark blue",0,0,139);break;
        case colors::DARK_BLUE_GRAY:return Color("Dark blue-gray",102,102,153);break;
        case colors::DARK_BROWN:return Color("Dark brown",101,67,33);break;
        case colors::DARK_BYZANTIUM:return Color("Dark byzantium",93,57,84);break;
        case colors::DARK_CANDY_APPLE_RED:return Color("Dark candy apple red",164,0,0);break;
        case colors::DARK_CERULEAN:return Color("Dark cerulean",8,69,126);break;
        case colors::DARK_CHESTNUT:return Color("Dark chestnut",152,105,96);break;
        case colors::DARK_CORAL:return Color("Dark coral",205,91,69);break;
        case colors::DARK_CYAN:return Color("Dark cyan",0,139,139);break;
        case colors::DARK_ELECTRIC_BLUE:return Color("Dark electric blue",83,104,120);break;
        case colors::DARK_GOLDENROD:return Color("Dark goldenrod",184,134,11);break;
        case colors::DARK_GRAY:return Color("Dark gray",169,169,169);break;
        case colors::DARK_GREEN:return Color("Dark green",1,50,32);break;
        case colors::DARK_IMPERIAL_BLUE:return Color("Dark imperial blue",0,65,106);break;
        case colors::DARK_JUNGLE_GREEN:return Color("Dark jungle green",26,36,33);break;
        case colors::DARK_KHAKI:return Color("Dark khaki",189,183,107);break;
        case colors::DARK_LAVA:return Color("Dark lava",72,60,50);break;
        case colors::DARK_LAVENDER:return Color("Dark lavender",115,79,150);break;
        case colors::DARK_LIVER:return Color("Dark liver",83,75,79);break;
        case colors::DARK_LIVER_HORSES:return Color("Dark liver (horses)",84,61,55);break;
        case colors::DARK_MAGENTA:return Color("Dark magenta",139,0,139);break;
        case colors::DARK_MIDNIGHT_BLUE:return Color("Dark midnight blue",0,51,102);break;
        case colors::DARK_MOSS_GREEN:return Color("Dark moss green",74,93,35);break;
        case colors::DARK_OLIVE_GREEN:return Color("Dark olive green",85,107,47);break;
        case colors::DARK_ORANGE:return Color("Dark orange",255,140,0);break;
        case colors::DARK_ORCHID:return Color("Dark orchid",153,50,204);break;
        case colors::DARK_PASTEL_BLUE:return Color("Dark pastel blue",119,158,203);break;
        case colors::DARK_PASTEL_GREEN:return Color("Dark pastel green",3,192,60);break;
        case colors::DARK_PASTEL_PURPLE:return Color("Dark pastel purple",150,111,214);break;
        case colors::DARK_PASTEL_RED:return Color("Dark pastel red",194,59,34);break;
        case colors::DARK_PINK:return Color("Dark pink",231,84,128);break;
        case colors::DARK_POWDER_BLUE:return Color("Dark powder blue",0,51,153);break;
        case colors::DARK_PUCE:return Color("Dark puce",79,58,60);break;
        case colors::DARK_RASPBERRY:return Color("Dark raspberry",135,38,87);break;
        case colors::DARK_RED:return Color("Dark red",139,0,0);break;
        case colors::DARK_SALMON:return Color("Dark salmon",233,150,122);break;
        case colors::DARK_SCARLET:return Color("Dark scarlet",86,3,25);break;
        case colors::DARK_SEA_GREEN:return Color("Dark sea green",143,188,143);break;
        case colors::DARK_SIENNA:return Color("Dark sienna",60,20,20);break;
        case colors::DARK_SKY_BLUE:return Color("Dark sky blue",140,190,214);break;
        case colors::DARK_SLATE_BLUE:return Color("Dark slate blue",72,61,139);break;
        case colors::DARK_SLATE_GRAY:return Color("Dark slate gray",47,79,79);break;
        case colors::DARK_SPRING_GREEN:return Color("Dark spring green",23,114,69);break;
        case colors::DARK_TAN:return Color("Dark tan",145,129,81);break;
        case colors::DARK_TANGERINE:return Color("Dark tangerine",255,168,18);break;
        case colors::DARK_TAUPE:return Color("Dark taupe",72,60,50);break;
        case colors::DARK_TERRA_COTTA:return Color("Dark terra cotta",204,78,92);break;
        case colors::DARK_TURQUOISE:return Color("Dark turquoise",0,206,209);break;
        case colors::DARK_VANILLA:return Color("Dark vanilla",209,190,168);break;
        case colors::DARK_VIOLET:return Color("Dark violet",148,0,211);break;
        case colors::DARK_YELLOW:return Color("Dark yellow",155,135,12);break;
        case colors::DARTMOUTH_GREEN:return Color("Dartmouth green",0,112,60);break;
        case colors::DAVYS_GREY:return Color("Davy-s grey",85,85,85);break;
        case colors::DEBIAN_RED:return Color("Debian red",215,10,83);break;
        case colors::DEEP_CARMINE:return Color("Deep carmine",169,32,62);break;
        case colors::DEEP_CARMINE_PINK:return Color("Deep carmine pink",239,48,56);break;
        case colors::DEEP_CARROT_ORANGE:return Color("Deep carrot orange",233,105,44);break;
        case colors::DEEP_CERISE:return Color("Deep cerise",218,50,135);break;
        case colors::DEEP_CHAMPAGNE:return Color("Deep champagne",250,214,165);break;
        case colors::DEEP_CHESTNUT:return Color("Deep chestnut",185,78,72);break;
        case colors::DEEP_COFFEE:return Color("Deep coffee",112,66,65);break;
        case colors::DEEP_FUCHSIA:return Color("Deep fuchsia",193,84,193);break;
        case colors::DEEP_JUNGLE_GREEN:return Color("Deep jungle green",0,75,73);break;
        case colors::DEEP_LEMON:return Color("Deep lemon",245,199,26);break;
        case colors::DEEP_LILAC:return Color("Deep lilac",153,85,187);break;
        case colors::DEEP_MAGENTA:return Color("Deep magenta",204,0,204);break;
        case colors::DEEP_MAUVE:return Color("Deep mauve",212,115,212);break;
        case colors::DEEP_MOSS_GREEN:return Color("Deep moss green",53,94,59);break;
        case colors::DEEP_PEACH:return Color("Deep peach",255,203,164);break;
        case colors::DEEP_PINK:return Color("Deep pink",255,20,147);break;
        case colors::DEEP_PUCE:return Color("Deep puce",169,92,104);break;
        case colors::DEEP_RUBY:return Color("Deep ruby",132,63,91);break;
        case colors::DEEP_SAFFRON:return Color("Deep saffron",255,153,51);break;
        case colors::DEEP_SAFFRON_ORANGE:return Color("Deep saffron orange",255,153,0);break;
        case colors::MIDNIGHT_MAROON: return Color("Midnight Maroon",153,51,102);
        case colors::DEEP_SKY_BLUE:return Color("Deep sky blue",0,191,255);break;
        case colors::DEEP_SPACE_SPARKLE:return Color("Deep Space Sparkle",74,100,108);break;
        case colors::DEEP_TAUPE:return Color("Deep Taupe",126,94,96);break;
        case colors::DEEP_TUSCAN_RED:return Color("Deep Tuscan red",102,66,77);break;
        case colors::DEER:return Color("Deer",186,135,89);break;
        case colors::DENIM:return Color("Denim",21,96,189);break;
        case colors::DESERT:return Color("Desert",193,154,107);break;
        case colors::DESERT_SAND:return Color("Desert sand",237,201,175);break;
        case colors::DESIRE:return Color("Desire",234,60,83);break;
        case colors::DIAMOND:return Color("Diamond",185,242,255);break;
        case colors::DIM_GRAY:return Color("Dim gray",105,105,105);break;
        case colors::DIRT:return Color("Dirt",155,118,83);break;
        case colors::DODGER_BLUE:return Color("Dodger blue",30,144,255);break;
        case colors::DOGWOOD_ROSE:return Color("Dogwood rose",215,24,104);break;
        case colors::DOLLAR_BILL:return Color("Dollar bill",133,187,101);break;
        case colors::DONKEY_BROWN:return Color("Donkey Brown",102,76,40);break;
        case colors::DRAB:return Color("Drab",150,113,23);break;
        case colors::DUKE_BLUE:return Color("Duke blue",0,0,156);break;
        case colors::DUST_STORM:return Color("Dust storm",229,204,201);break;
        case colors::DUTCH_WHITE:return Color("Dutch white",239,223,187);break;
        case colors::EARTH_YELLOW:return Color("Earth yellow",225,169,95);break;
        case colors::EBONY:return Color("Ebony",85,93,80);break;
        case colors::ECRU:return Color("Ecru",194,178,128);break;
        case colors::EERIE_BLACK:return Color("Eerie black",27,27,27);break;
        case colors::EGGPLANT:return Color("Eggplant",97,64,81);break;
        case colors::EGGSHELL:return Color("Eggshell",240,234,214);break;
        case colors::EGYPTIAN_BLUE:return Color("Egyptian blue",16,52,166);break;
        case colors::ELECTRIC_BLUE:return Color("Electric blue",125,249,255);break;
        case colors::ELECTRIC_CRIMSON:return Color("Electric crimson",255,0,63);break;
        case colors::ELECTRIC_CYAN:return Color("Electric cyan",0,255,255);break;
        case colors::ELECTRIC_GREEN:return Color("Electric green",0,255,0);break;
        case colors::ELECTRIC_INDIGO:return Color("Electric indigo",111,0,255);break;
        case colors::ELECTRIC_LAVENDER:return Color("Electric lavender",244,187,255);break;
        case colors::ELECTRIC_LIME:return Color("Electric lime",204,255,0);break;
        case colors::ELECTRIC_PURPLE:return Color("Electric purple",191,0,255);break;
        case colors::ELECTRIC_ULTRAMARINE:return Color("Electric ultramarine",63,0,255);break;
        case colors::ELECTRIC_VIOLET:return Color("Electric violet",143,0,255);break;
        case colors::ELECTRIC_YELLOW:return Color("Electric yellow",255,255,0);break;
        case colors::EMERALD:return Color("Emerald",80,200,120);break;
        case colors::EMINENCE:return Color("Eminence",108,48,130);break;
        case colors::ENGLISH_GREEN:return Color("English green",27,77,62);break;
        case colors::ENGLISH_LAVENDER:return Color("English lavender",180,131,149);break;
        case colors::ENGLISH_RED:return Color("English red",171,75,82);break;
        case colors::ENGLISH_VIOLET:return Color("English violet",86,60,92);break;
        case colors::ETON_BLUE:return Color("Eton blue",150,200,162);break;
        case colors::EUCALYPTUS:return Color("Eucalyptus",68,215,168);break;
        case colors::FALLOW:return Color("Fallow",193,154,107);break;
        case colors::FALU_RED:return Color("Falu red",128,24,24);break;
        case colors::FANDANGO:return Color("Fandango",181,51,137);break;
        case colors::FANDANGO_PINK:return Color("Fandango pink",222,82,133);break;
        case colors::FASHION_FUCHSIA:return Color("Fashion fuchsia",244,0,161);break;
        case colors::FAWN:return Color("Fawn",229,170,112);break;
        case colors::FELDGRAU:return Color("Feldgrau",77,93,83);break;
        case colors::FELDSPAR:return Color("Feldspar",253,213,177);break;
        case colors::FERN_GREEN:return Color("Fern green",79,121,66);break;
        case colors::FERRARI_RED:return Color("Ferrari Red",255,40,0);break;
        case colors::FIELD_DRAB:return Color("Field drab",108,84,30);break;
        case colors::FIREBRICK:return Color("Firebrick",178,34,34);break;
        case colors::FIRE_ENGINE_RED:return Color("Fire engine red",206,32,41);break;
        case colors::FLAME:return Color("Flame",226,88,34);break;
        case colors::FLAMINGO_PINK:return Color("Flamingo pink",252,142,172);break;
        case colors::FLATTERY:return Color("Flattery",107,68,35);break;
        case colors::FLAVESCENT:return Color("Flavescent",247,233,142);break;
        case colors::FLAX:return Color("Flax",238,220,130);break;
        case colors::FLIRT:return Color("Flirt",162,0,109);break;
        case colors::FLORAL_WHITE:return Color("Floral white",255,250,240);break;
        case colors::FLUORESCENT_ORANGE:return Color("Fluorescent orange",255,191,0);break;
        case colors::FLUORESCENT_PINK:return Color("Fluorescent pink",255,20,147);break;
        case colors::FLUORESCENT_YELLOW:return Color("Fluorescent yellow",204,255,0);break;
        case colors::FOLLY:return Color("Folly",255,0,79);break;
        case colors::FOREST_GREEN_TRADITIONAL:return Color("Forest green (traditional)",1,68,33);break;
        case colors::FOREST_GREEN_WEB:return Color("Forest green (web)",34,139,34);break;
        case colors::FRENCH_BEIGE:return Color("French beige",166,123,91);break;
        case colors::FRENCH_BISTRE:return Color("French bistre",133,109,77);break;
        case colors::FRENCH_BLUE:return Color("French blue",0,114,187);break;
        case colors::FRENCH_FUCHSIA:return Color("French fuchsia",253,63,146);break;
        case colors::FRENCH_LILAC:return Color("French lilac",134,96,142);break;
        case colors::FRENCH_LIME:return Color("French lime",158,253,56);break;
        case colors::FRENCH_MAUVE:return Color("French mauve",212,115,212);break;
        case colors::FRENCH_PINK:return Color("French pink",253,108,158);break;
        case colors::FRENCH_PUCE:return Color("French puce",78,22,9);break;
        case colors::FRENCH_RASPBERRY:return Color("French raspberry",199,44,72);break;
        case colors::FRENCH_ROSE:return Color("French rose",246,74,138);break;
        case colors::FRENCH_SKY_BLUE:return Color("French sky blue",119,181,254);break;
        case colors::FRENCH_VIOLET:return Color("French violet",136,6,206);break;
        case colors::FRENCH_WINE:return Color("French wine",172,30,68);break;
        case colors::FRESH_AIR:return Color("Fresh Air",166,231,255);break;
        case colors::FUCHSIA:return Color("Fuchsia",255,0,255);break;
        case colors::FUCHSIA_CRAYOLA:return Color("Fuchsia (Crayola)",193,84,193);break;
        case colors::FUCHSIA_PINK:return Color("Fuchsia pink",255,119,255);break;
        case colors::FUCHSIA_PURPLE:return Color("Fuchsia purple",204,57,123);break;
        case colors::FUCHSIA_ROSE:return Color("Fuchsia rose",199,67,117);break;
        case colors::FULVOUS:return Color("Fulvous",228,132,0);break;
        case colors::FUZZY_WUZZY:return Color("Fuzzy Wuzzy",204,102,102);break;
        case colors::GAINSBORO:return Color("Gainsboro",220,220,220);break;
        case colors::GAMBOGE:return Color("Gamboge",228,155,15);break;
        case colors::GENERIC_VIRIDIAN:return Color("Generic viridian",0,127,102);break;
        case colors::GHOST_WHITE:return Color("Ghost white",248,248,255);break;
        case colors::GIANTS_ORANGE:return Color("Giants orange",254,90,29);break;
        case colors::GINGER:return Color("Ginger",176,101,0);break;
        case colors::GLAUCOUS:return Color("Glaucous",96,130,182);break;
        case colors::GLITTER:return Color("Glitter",230,232,250);break;
        case colors::GO_GREEN:return Color("GO green",0,171,102);break;
        case colors::GOLD_METALLIC:return Color("Gold (metallic)",212,175,55);break;
        case colors::GOLD_WEB_GOLDEN:return Color("Gold (web) (Golden)",255,215,0);break;
        case colors::GOLD_FUSION:return Color("Gold Fusion",133,117,78);break;
        case colors::GOLDEN_BROWN:return Color("Golden brown",153,101,21);break;
        case colors::GOLDEN_POPPY:return Color("Golden poppy",252,194,0);break;
        case colors::GOLDEN_YELLOW:return Color("Golden yellow",255,223,0);break;
        case colors::GOLDENROD:return Color("Goldenrod",218,165,32);break;
        case colors::GRANNY_SMITH_APPLE:return Color("Granny Smith Apple",168,228,160);break;
        case colors::GRAPE:return Color("Grape",111,45,168);break;
        case colors::GRAY:return Color("Gray",128,128,128);break;
        case colors::GRAY_HTML_CSS_GRAY:return Color("Gray (HTML/CSS gray)",128,128,128);break;
        case colors::GRAY_X11_GRAY:return Color("Gray (X11 gray)",190,190,190);break;
        case colors::GRAY_ASPARAGUS:return Color("Gray-asparagus",70,89,69);break;
        case colors::GRAY_BLUE:return Color("Gray-blue",140,146,172);break;
        case colors::GREEN_COLOR_WHEEL_X11_GREEN:return Color("Green (Color Wheel) (X11 green)",0,255,0);break;
        case colors::GREEN_CRAYOLA:return Color("Green (Crayola)",28,172,120);break;
        case colors::GREEN_HTML_CSS_COLOR:return Color("Green (HTML/CSS color)",0,128,0);break;
        case colors::GREEN_MUNSELL:return Color("Green (Munsell)",0,168,119);break;
        case colors::GREEN_NCS:return Color("Green (NCS)",0,159,107);break;
        case colors::GREEN_PIGMENT:return Color("Green (pigment)",0,165,80);break;
        case colors::GREEN_RYB:return Color("Green (RYB)",102,176,50);break;
        case colors::GREEN_YELLOW:return Color("Green-yellow",173,255,47);break;
        case colors::GRULLO:return Color("Grullo",169,154,134);break;
        case colors::GUPPIE_GREEN:return Color("Guppie green",0,255,127);break;
        case colors::HALAYA_UBE:return Color("Halaya ube",102,56,84);break;
        case colors::HAN_BLUE:return Color("Han blue",68,108,207);break;
        case colors::HAN_PURPLE:return Color("Han purple",82,24,250);break;
        case colors::HANSA_YELLOW:return Color("Hansa yellow",233,214,107);break;
        case colors::HARLEQUIN:return Color("Harlequin",63,255,0);break;
        case colors::HARVARD_CRIMSON:return Color("Harvard crimson",201,0,22);break;
        case colors::HARVEST_GOLD:return Color("Harvest gold",218,145,0);break;
        case colors::HEART_GOLD:return Color("Heart Gold",128,128,0);break;
        case colors::HELIOTROPE:return Color("Heliotrope",223,115,255);break;
        case colors::HELIOTROPE_GRAY:return Color("Heliotrope gray",170,152,169);break;
        case colors::HOLLYWOOD_CERISE:return Color("Hollywood cerise",244,0,161);break;
        case colors::HONEYDEW:return Color("Honeydew",240,255,240);break;
        case colors::HONOLULU_BLUE:return Color("Honolulu blue",0,109,176);break;
        case colors::HOOKERS_GREEN:return Color("Hooker-s green",73,121,107);break;
        case colors::HOT_MAGENTA:return Color("Hot magenta",255,29,206);break;
        case colors::HOT_PINK:return Color("Hot pink",255,105,180);break;
        case colors::HUNTER_GREEN:return Color("Hunter green",53,94,59);break;
        case colors::ICEBERG:return Color("Iceberg",113,166,210);break;
        case colors::ICTERINE:return Color("Icterine",252,247,94);break;
        case colors::ILLUMINATING_EMERALD:return Color("Illuminating Emerald",49,145,119);break;
        case colors::IMPERIAL:return Color("Imperial",96,47,107);break;
        case colors::IMPERIAL_BLUE:return Color("Imperial blue",0,35,149);break;
        case colors::IMPERIAL_PURPLE:return Color("Imperial purple",102,2,60);break;
        case colors::IMPERIAL_RED:return Color("Imperial red",237,41,57);break;
        case colors::INCHWORM:return Color("Inchworm",178,236,93);break;
        case colors::INDEPENDENCE:return Color("Independence",76,81,109);break;
        case colors::INDIA_GREEN:return Color("India green",19,136,8);break;
        case colors::INDIAN_RED:return Color("Indian red",205,92,92);break;
        case colors::INDIAN_YELLOW:return Color("Indian yellow",227,168,87);break;
        case colors::INDIGO:return Color("Indigo",111,0,255);break;
        case colors::INDIGO_DYE:return Color("Indigo dye",9,31,146);break;
        case colors::INDIGO_WEB:return Color("Indigo (web)",75,0,130);break;
        case colors::INTERNATIONAL_KLEIN_BLUE:return Color("International Klein Blue",0,47,167);break;
        case colors::INTERNATIONAL_ORANGE_AEROSPACE:return Color("International orange (aerospace)",255,79,0);break;
        case colors::INTERNATIONAL_ORANGE_ENGINEERING:return Color("International orange (engineering)",186,22,12);break;
        case colors::INTERNATIONAL_ORANGE_GOLDEN_GATE_BRIDGE:return Color("International orange (Golden Gate Bridge)",192,54,44);break;
        case colors::IRIS:return Color("Iris",90,79,207);break;
        case colors::IRRESISTIBLE:return Color("Irresistible",179,68,108);break;
        case colors::ISABELLINE:return Color("Isabelline",244,240,236);break;
        case colors::ISLAMIC_GREEN:return Color("Islamic green",0,144,0);break;
        case colors::ITALIAN_SKY_BLUE:return Color("Italian sky blue",178,255,255);break;
        case colors::IVORY:return Color("Ivory",255,255,240);break;
        case colors::JADE:return Color("Jade",0,168,107);break;
        case colors::JAPANESE_CARMINE:return Color("Japanese carmine",157,41,51);break;
        case colors::JAPANESE_INDIGO:return Color("Japanese indigo",38,67,72);break;
        case colors::JAPANESE_VIOLET:return Color("Japanese violet",91,50,86);break;
        case colors::JASMINE:return Color("Jasmine",248,222,126);break;
        case colors::JASPER:return Color("Jasper",215,59,62);break;
        case colors::JAZZBERRY_JAM:return Color("Jazzberry jam",165,11,94);break;
        case colors::JELLY_BEAN:return Color("Jelly Bean",218,97,78);break;
        case colors::JET:return Color("Jet",52,52,52);break;
        case colors::JONQUIL:return Color("Jonquil",244,202,22);break;
        case colors::JORDY_BLUE:return Color("Jordy blue",138,185,241);break;
        case colors::JUNE_BUD:return Color("June bud",189,218,87);break;
        case colors::JUNGLE_GREEN:return Color("Jungle green",41,171,135);break;
        case colors::KELLY_GREEN:return Color("Kelly green",76,187,23);break;
        case colors::KENYAN_COPPER:return Color("Kenyan copper",124,28,5);break;
        case colors::KEPPEL:return Color("Keppel",58,176,158);break;
        case colors::KHAKI_HTML_CSS_KHAKI:return Color("Khaki (HTML/CSS) (Khaki)",195,176,145);break;
        case colors::KHAKI_X11_LIGHT_KHAKI:return Color("Khaki (X11) (Light khaki)",240,230,140);break;
        case colors::KOBE:return Color("Kobe",136,45,23);break;
        case colors::KOBI:return Color("Kobi",231,159,196);break;
        case colors::KOMBU_GREEN:return Color("Kombu green",53,66,48);break;
        case colors::KU_CRIMSON:return Color("KU Crimson",232,0,13);break;
        case colors::LA_SALLE_GREEN:return Color("La Salle Green",8,120,48);break;
        case colors::LANGUID_LAVENDER:return Color("Languid lavender",214,202,221);break;
        case colors::LAPIS_LAZULI:return Color("Lapis lazuli",38,97,156);break;
        case colors::LASER_LEMON:return Color("Laser Lemon",255,255,102);break;
        case colors::LAUREL_GREEN:return Color("Laurel green",169,186,157);break;
        case colors::LAVA:return Color("Lava",207,16,32);break;
        case colors::LAVENDER_FLORAL:return Color("Lavender (floral)",181,126,220);break;
        case colors::LAVENDER_WEB:return Color("Lavender (web)",230,230,250);break;
        case colors::LAVENDER_BLUE:return Color("Lavender blue",204,204,255);break;
        case colors::LAVENDER_BLUSH:return Color("Lavender blush",255,240,245);break;
        case colors::LAVENDER_GRAY:return Color("Lavender gray",196,195,208);break;
        case colors::LAVENDER_INDIGO:return Color("Lavender indigo",148,87,235);break;
        case colors::LAVENDER_MAGENTA:return Color("Lavender magenta",238,130,238);break;
        case colors::LAVENDER_MIST:return Color("Lavender mist",230,230,250);break;
        case colors::LAVENDER_PINK:return Color("Lavender pink",251,174,210);break;
        case colors::LAVENDER_PURPLE:return Color("Lavender purple",150,123,182);break;
        case colors::LAVENDER_ROSE:return Color("Lavender rose",251,160,227);break;
        case colors::LAWN_GREEN:return Color("Lawn green",124,252,0);break;
        case colors::LEMON:return Color("Lemon",255,247,0);break;
        case colors::LEMON_CHIFFON:return Color("Lemon chiffon",255,250,205);break;
        case colors::LEMON_CURRY:return Color("Lemon curry",204,160,29);break;
        case colors::LEMON_GLACIER:return Color("Lemon glacier",253,255,0);break;
        case colors::LEMON_LIME:return Color("Lemon lime",227,255,0);break;
        case colors::LEMON_MERINGUE:return Color("Lemon meringue",246,234,190);break;
        case colors::LEMON_YELLOW:return Color("Lemon yellow",255,244,79);break;
        case colors::LICORICE:return Color("Licorice",26,17,16);break;
        case colors::LIBERTY:return Color("Liberty",84,90,167);break;
        case colors::LIGHT_APRICOT:return Color("Light apricot",253,213,177);break;
        case colors::LIGHT_BLUE:return Color("Light blue",173,216,230);break;
        case colors::LIGHT_BROWN:return Color("Light brown",181,101,29);break;
        case colors::LIGHT_CARMINE_PINK:return Color("Light carmine pink",230,103,113);break;
        case colors::LIGHT_CORAL:return Color("Light coral",240,128,128);break;
        case colors::LIGHT_CORNFLOWER_BLUE:return Color("Light cornflower blue",147,204,234);break;
        case colors::LIGHT_CRIMSON:return Color("Light crimson",245,105,145);break;
        case colors::LIGHT_CYAN:return Color("Light cyan",224,255,255);break;
        case colors::LIGHT_DEEP_PINK:return Color("Light deep pink",255,92,205);break;
        case colors::LIGHT_FUCHSIA_PINK:return Color("Light fuchsia pink",249,132,239);break;
        case colors::LIGHT_GOLDENROD_YELLOW:return Color("Light goldenrod yellow",250,250,210);break;
        case colors::LIGHT_GRAY:return Color("Light gray",211,211,211);break;
        case colors::LIGHT_GREEN:return Color("Light green",144,238,144);break;
        case colors::LIGHT_HOT_PINK:return Color("Light hot pink",255,179,222);break;
        case colors::LIGHT_KHAKI:return Color("Light khaki",240,230,140);break;
        case colors::LIGHT_MEDIUM_ORCHID:return Color("Light medium orchid",211,155,203);break;
        case colors::LIGHT_MOSS_GREEN:return Color("Light moss green",173,223,173);break;
        case colors::LIGHT_ORCHID:return Color("Light orchid",230,168,215);break;
        case colors::LIGHT_PASTEL_PURPLE:return Color("Light pastel purple",177,156,217);break;
        case colors::LIGHT_PINK:return Color("Light pink",255,182,193);break;
        case colors::LIGHT_RED_OCHRE:return Color("Light red ochre",233,116,81);break;
        case colors::LIGHT_SALMON:return Color("Light salmon",255,160,122);break;
        case colors::LIGHT_SALMON_PINK:return Color("Light salmon pink",255,153,153);break;
        case colors::LIGHT_SEA_GREEN:return Color("Light sea green",32,178,170);break;
        case colors::LIGHT_SKY_BLUE:return Color("Light sky blue",135,206,250);break;
        case colors::LIGHT_SLATE_GRAY:return Color("Light slate gray",119,136,153);break;
        case colors::LIGHT_STEEL_BLUE:return Color("Light steel blue",176,196,222);break;
        case colors::LIGHT_TAUPE:return Color("Light taupe",179,139,109);break;
        case colors::LIGHT_THULIAN_PINK:return Color("Light Thulian pink",230,143,172);break;
        case colors::LIGHT_YELLOW:return Color("Light yellow",255,255,224);break;
        case colors::LILAC:return Color("Lilac",200,162,200);break;
        case colors::LIME_COLOR_WHEEL:return Color("Lime (color wheel)",191,255,0);break;
        case colors::LIME_WEB_X11_GREEN:return Color("Lime (web) (X11 green)",0,255,0);break;
        case colors::LIME_GREEN:return Color("Lime green",50,205,50);break;
        case colors::LIMERICK:return Color("Limerick",157,194,9);break;
        case colors::LINCOLN_GREEN:return Color("Lincoln green",25,89,5);break;
        case colors::LINEN:return Color("Linen",250,240,230);break;
        case colors::LION:return Color("Lion",193,154,107);break;
        case colors::LISERAN_PURPLE:return Color("Liseran Purple",222,111,161);break;
        case colors::LITTLE_BOY_BLUE:return Color("Little boy blue",108,160,220);break;
        case colors::LIVER:return Color("Liver",103,76,71);break;
        case colors::LIVER_DOGS:return Color("Liver (dogs)",184,109,41);break;
        case colors::LIVER_ORGAN:return Color("Liver (organ)",108,46,31);break;
        case colors::LIVER_CHESTNUT:return Color("Liver chestnut",152,116,86);break;
        case colors::LIVID:return Color("Livid",102,153,204);break;
        case colors::LUMBER:return Color("Lumber",255,228,205);break;
        case colors::LUST:return Color("Lust",230,32,32);break;
        case colors::MAGENTA:return Color("Magenta",255,0,255);break;
        case colors::MAGENTA_CRAYOLA:return Color("Magenta (Crayola)",255,85,163);break;
        case colors::MAGENTA_DYE:return Color("Magenta (dye)",202,31,123);break;
        case colors::MAGENTA_PANTONE:return Color("Magenta (Pantone)",208,65,126);break;
        case colors::MAGENTA_PROCESS:return Color("Magenta (process)",255,0,144);break;
        case colors::MAGENTA_HAZE:return Color("Magenta haze",159,69,118);break;
        case colors::MAGIC_MINT:return Color("Magic mint",170,240,209);break;
        case colors::MAGNOLIA:return Color("Magnolia",248,244,255);break;
        case colors::MAHOGANY:return Color("Mahogany",192,64,0);break;
        case colors::MAIZE:return Color("Maize",251,236,93);break;
        case colors::MAJORELLE_BLUE:return Color("Majorelle Blue",96,80,220);break;
        case colors::MALACHITE:return Color("Malachite",11,218,81);break;
        case colors::MANATEE:return Color("Manatee",151,154,170);break;
        case colors::MANGO_TANGO:return Color("Mango Tango",255,130,67);break;
        case colors::MANTIS:return Color("Mantis",116,195,101);break;
        case colors::MARDI_GRAS:return Color("Mardi Gras",136,0,133);break;
        case colors::MAROON_CRAYOLA:return Color("Maroon (Crayola)",195,33,72);break;
        case colors::MAROON_HTML_CSS:return Color("Maroon (HTML/CSS)",128,0,0);break;
        case colors::MAROON_X11:return Color("Maroon (X11)",176,48,96);break;
        case colors::MAUVE:return Color("Mauve",224,176,255);break;
        case colors::MAUVE_TAUPE:return Color("Mauve taupe",145,95,109);break;
        case colors::MAUVELOUS:return Color("Mauvelous",239,152,170);break;
        case colors::MAY_GREEN:return Color("May green",76,145,65);break;
        case colors::MAYA_BLUE:return Color("Maya blue",115,194,251);break;
        case colors::MEAT_BROWN:return Color("Meat brown",229,183,59);break;
        case colors::MEDIUM_AQUAMARINE:return Color("Medium aquamarine",102,221,170);break;
        case colors::MEDIUM_BLUE:return Color("Medium blue",0,0,205);break;
        case colors::MEDIUM_CANDY_APPLE_RED:return Color("Medium candy apple red",226,6,44);break;
        case colors::MEDIUM_CARMINE:return Color("Medium carmine",175,64,53);break;
        case colors::MEDIUM_CHAMPAGNE:return Color("Medium champagne",243,229,171);break;
        case colors::MEDIUM_ELECTRIC_BLUE:return Color("Medium electric blue",3,80,150);break;
        case colors::MEDIUM_JUNGLE_GREEN:return Color("Medium jungle green",28,53,45);break;
        case colors::MEDIUM_LAVENDER_MAGENTA:return Color("Medium lavender magenta",221,160,221);break;
        case colors::MEDIUM_ORCHID:return Color("Medium orchid",186,85,211);break;
        case colors::MEDIUM_PERSIAN_BLUE:return Color("Medium Persian blue",0,103,165);break;
        case colors::MEDIUM_PURPLE:return Color("Medium purple",147,112,219);break;
        case colors::MEDIUM_RED_VIOLET:return Color("Medium red-violet",187,51,133);break;
        case colors::MEDIUM_RUBY:return Color("Medium ruby",170,64,105);break;
        case colors::MEDIUM_SEA_GREEN:return Color("Medium sea green",60,179,113);break;
        case colors::MEDIUM_SKY_BLUE:return Color("Medium sky blue",128,218,235);break;
        case colors::MEDIUM_SLATE_BLUE:return Color("Medium slate blue",123,104,238);break;
        case colors::MEDIUM_SPRING_BUD:return Color("Medium spring bud",201,220,135);break;
        case colors::MEDIUM_SPRING_GREEN:return Color("Medium spring green",0,250,154);break;
        case colors::MEDIUM_TAUPE:return Color("Medium taupe",103,76,71);break;
        case colors::MEDIUM_TURQUOISE:return Color("Medium turquoise",72,209,204);break;
        case colors::MEDIUM_TUSCAN_RED:return Color("Medium Tuscan red",121,68,59);break;
        case colors::MEDIUM_VERMILION:return Color("Medium vermilion",217,96,59);break;
        case colors::MEDIUM_VIOLET_RED:return Color("Medium violet-red",199,21,133);break;
        case colors::MELLOW_APRICOT:return Color("Mellow apricot",248,184,120);break;
        case colors::MELLOW_YELLOW:return Color("Mellow yellow",248,222,126);break;
        case colors::MELON:return Color("Melon",253,188,180);break;
        case colors::METALLIC_SEAWEED:return Color("Metallic Seaweed",10,126,140);break;
        case colors::METALLIC_SUNBURST:return Color("Metallic Sunburst",156,124,56);break;
        case colors::MEXICAN_PINK:return Color("Mexican pink",228,0,124);break;
        case colors::MIDNIGHT_BLUE:return Color("Midnight blue",25,25,112);break;
        case colors::MIDNIGHT_GREEN_EAGLE_GREEN:return Color("Midnight green (eagle green)",0,73,83);break;
        case colors::MIKADO_YELLOW:return Color("Mikado yellow",255,196,12);break;
        case colors::MINDARO:return Color("Mindaro",227,249,136);break;
        case colors::MINT:return Color("Mint",62,180,137);break;
        case colors::MINT_CREAM:return Color("Mint cream",245,255,250);break;
        case colors::MINT_GREEN:return Color("Mint green",152,255,152);break;
        case colors::MISTY_ROSE:return Color("Misty rose",255,228,225);break;
        case colors::MOCCASIN:return Color("Moccasin",250,235,215);break;
        case colors::MODE_BEIGE:return Color("Mode beige",150,113,23);break;
        case colors::MOONSTONE_BLUE:return Color("Moonstone blue",115,169,194);break;
        case colors::MORDANT_RED_19:return Color("Mordant red 19",174,12,0);break;
        case colors::MOSS_GREEN:return Color("Moss green",138,154,91);break;
        case colors::MOUNTAIN_MEADOW:return Color("Mountain Meadow",48,186,143);break;
        case colors::MOUNTBATTEN_PINK:return Color("Mountbatten pink",153,122,141);break;
        case colors::MSU_GREEN:return Color("MSU Green",24,69,59);break;
        case colors::MUGHAL_GREEN:return Color("Mughal green",48,96,48);break;
        case colors::MULBERRY:return Color("Mulberry",197,75,140);break;
        case colors::MUSTARD:return Color("Mustard",255,219,88);break;
        case colors::MYRTLE_GREEN:return Color("Myrtle green",49,120,115);break;
        case colors::NADESHIKO_PINK:return Color("Nadeshiko pink",246,173,198);break;
        case colors::NAPIER_GREEN:return Color("Napier green",42,128,0);break;
        case colors::NAPLES_YELLOW:return Color("Naples yellow",250,218,94);break;
        case colors::NAVAJO_WHITE:return Color("Navajo white",255,222,173);break;
        case colors::NAVY:return Color("Navy",0,0,128);break;
        case colors::NAVY_PURPLE:return Color("Navy purple",148,87,235);break;
        case colors::NEON_CARROT:return Color("Neon Carrot",255,163,67);break;
        case colors::NEON_FUCHSIA:return Color("Neon fuchsia",254,65,100);break;
        case colors::NEON_GREEN:return Color("Neon green",57,255,20);break;
        case colors::NEW_CAR:return Color("New Car",33,79,198);break;
        case colors::NEW_YORK_PINK:return Color("New York pink",215,131,127);break;
        case colors::NON_PHOTO_BLUE:return Color("Non-photo blue",164,221,237);break;
        case colors::NORTH_TEXAS_GREEN:return Color("North Texas Green",5,144,51);break;
        case colors::NYANZA:return Color("Nyanza",233,255,219);break;
        case colors::OCEAN_BOAT_BLUE:return Color("Ocean Boat Blue",0,119,190);break;
        case colors::OCHRE:return Color("Ochre",204,119,34);break;
        case colors::OFFICE_GREEN:return Color("Office green",0,128,0);break;
        case colors::OLD_BURGUNDY:return Color("Old burgundy",67,48,46);break;
        case colors::OLD_GOLD:return Color("Old gold",207,181,59);break;
        case colors::OLD_HELIOTROPE:return Color("Old heliotrope",86,60,92);break;
        case colors::OLD_LACE:return Color("Old lace",253,245,230);break;
        case colors::OLD_LAVENDER:return Color("Old lavender",121,104,120);break;
        case colors::OLD_MAUVE:return Color("Old mauve",103,49,71);break;
        case colors::OLD_MOSS_GREEN:return Color("Old moss green",134,126,54);break;
        case colors::OLD_ROSE:return Color("Old rose",192,128,129);break;
        case colors::OLD_SILVER:return Color("Old silver",132,132,130);break;
        case colors::OLIVE:return Color("Olive",128,128,0);break;
        case colors::OLIVE_DRAB_3:return Color("Olive Drab (3)",107,142,35);break;
        case colors::OLIVE_DRAB_7:return Color("Olive Drab 7",60,52,31);break;
        case colors::OLIVINE:return Color("Olivine",154,185,115);break;
        case colors::ONYX:return Color("Onyx",53,56,57);break;
        case colors::OPERA_MAUVE:return Color("Opera mauve",183,132,167);break;
        case colors::ORANGE_COLOR_WHEEL:return Color("Orange (color wheel)",255,127,0);break;
        case colors::ORANGE_CRAYOLA:return Color("Orange (Crayola)",255,117,56);break;
        case colors::ORANGE_PANTONE:return Color("Orange (Pantone)",255,88,0);break;
        case colors::ORANGE_RYB:return Color("Orange (RYB)",251,153,2);break;
        case colors::ORANGE_WEB:return Color("Orange (web)",255,165,0);break;
        case colors::ORANGE_PEEL:return Color("Orange peel",255,159,0);break;
        case colors::ORANGE_RED:return Color("Orange-red",255,69,0);break;
        case colors::ORCHID:return Color("Orchid",218,112,214);break;
        case colors::ORCHID_PINK:return Color("Orchid pink",242,189,205);break;
        case colors::ORIOLES_ORANGE:return Color("Orioles orange",251,79,20);break;
        case colors::OTTER_BROWN:return Color("Otter brown",101,67,33);break;
        case colors::OUTER_SPACE:return Color("Outer Space",65,74,76);break;
        case colors::OUTRAGEOUS_ORANGE:return Color("Outrageous Orange",255,110,74);break;
        case colors::OXFORD_BLUE:return Color("Oxford Blue",0,33,71);break;
        case colors::OU_CRIMSON_RED:return Color("OU Crimson Red",153,0,0);break;
        case colors::PAKISTAN_GREEN:return Color("Pakistan green",0,102,0);break;
        case colors::PALATINATE_BLUE:return Color("Palatinate blue",39,59,226);break;
        case colors::PALATINATE_PURPLE:return Color("Palatinate purple",104,40,96);break;
        case colors::PALE_AQUA:return Color("Pale aqua",188,212,230);break;
        case colors::PALE_BLUE:return Color("Pale blue",175,238,238);break;
        case colors::PALE_BROWN:return Color("Pale brown",152,118,84);break;
        case colors::PALE_CARMINE:return Color("Pale carmine",175,64,53);break;
        case colors::PALE_CERULEAN:return Color("Pale cerulean",155,196,226);break;
        case colors::PALE_CHESTNUT:return Color("Pale chestnut",221,173,175);break;
        case colors::PALE_COPPER:return Color("Pale copper",218,138,103);break;
        case colors::PALE_CORNFLOWER_BLUE:return Color("Pale cornflower blue",171,205,239);break;
        case colors::PALE_GOLD:return Color("Pale gold",230,190,138);break;
        case colors::PALE_GOLDENROD:return Color("Pale goldenrod",238,232,170);break;
        case colors::PALE_GREEN:return Color("Pale green",152,251,152);break;
        case colors::PALE_LAVENDER:return Color("Pale lavender",220,208,255);break;
        case colors::PALE_MAGENTA:return Color("Pale magenta",249,132,229);break;
        case colors::PALE_PINK:return Color("Pale pink",250,218,221);break;
        case colors::PALE_PLUM:return Color("Pale plum",221,160,221);break;
        case colors::PALE_RED_VIOLET:return Color("Pale red-violet",219,112,147);break;
        case colors::PALE_ROBIN_EGG_BLUE:return Color("Pale robin egg blue",150,222,209);break;
        case colors::PALE_SILVER:return Color("Pale silver",201,192,187);break;
        case colors::PALE_SPRING_BUD:return Color("Pale spring bud",236,235,189);break;
        case colors::PALE_TAUPE:return Color("Pale taupe",188,152,126);break;
        case colors::PALE_TURQUOISE:return Color("Pale turquoise",175,238,238);break;
        case colors::PALE_VIOLET_RED:return Color("Pale violet-red",219,112,147);break;
        case colors::PANSY_PURPLE:return Color("Pansy purple",120,24,74);break;
        case colors::PAOLO_VERONESE_GREEN:return Color("Paolo Veronese green",0,155,125);break;
        case colors::PAPAYA_WHIP:return Color("Papaya whip",255,239,213);break;
        case colors::PARADISE_PINK:return Color("Paradise pink",230,62,98);break;
        case colors::PARIS_GREEN:return Color("Paris Green",80,200,120);break;
        case colors::PASTEL_BLUE:return Color("Pastel blue",174,198,207);break;
        case colors::PASTEL_BROWN:return Color("Pastel brown",131,105,83);break;
        case colors::PASTEL_GRAY:return Color("Pastel gray",207,207,196);break;
        case colors::PASTEL_GREEN:return Color("Pastel green",119,221,119);break;
        case colors::PASTEL_MAGENTA:return Color("Pastel magenta",244,154,194);break;
        case colors::PASTEL_ORANGE:return Color("Pastel orange",255,179,71);break;
        case colors::PASTEL_PINK:return Color("Pastel pink",222,165,164);break;
        case colors::PASTEL_PURPLE:return Color("Pastel purple",179,158,181);break;
        case colors::PASTEL_RED:return Color("Pastel red",255,105,97);break;
        case colors::PASTEL_VIOLET:return Color("Pastel violet",203,153,201);break;
        case colors::PASTEL_YELLOW:return Color("Pastel yellow",253,253,150);break;
        case colors::PATRIARCH:return Color("Patriarch",128,0,128);break;
        case colors::PAYNES_GREY:return Color("Payne-s grey",83,104,120);break;
        case colors::PEACH:return Color("Peach",255,229,180);break;
        case colors::PEACH_2_POINT_OH:return Color("Peach",255,203,164);break;
        case colors::WHITE_RED:return Color("White Red",255,204,204);break;
        case colors::PEACH_ORANGE:return Color("Peach-orange",255,204,153);break;
        case colors::PEACH_PUFF:return Color("Peach puff",255,218,185);break;
        case colors::PEACH_YELLOW:return Color("Peach-yellow",250,223,173);break;
        case colors::PEAR:return Color("Pear",209,226,49);break;
        case colors::PEARL:return Color("Pearl",234,224,200);break;
        case colors::PEARL_AQUA:return Color("Pearl Aqua",136,216,192);break;
        case colors::PEARLY_PURPLE:return Color("Pearly purple",183,104,162);break;
        case colors::PERIDOT:return Color("Peridot",230,226,0);break;
        case colors::PERIWINKLE:return Color("Periwinkle",204,204,255);break;
        case colors::PERSIAN_BLUE:return Color("Persian blue",28,57,187);break;
        case colors::PERSIAN_GREEN:return Color("Persian green",0,166,147);break;
        case colors::PERSIAN_INDIGO:return Color("Persian indigo",50,18,122);break;
        case colors::PERSIAN_ORANGE:return Color("Persian orange",217,144,88);break;
        case colors::PERSIAN_PINK:return Color("Persian pink",247,127,190);break;
        case colors::PERSIAN_PLUM:return Color("Persian plum",112,28,28);break;
        case colors::PERSIAN_RED:return Color("Persian red",204,51,51);break;
        case colors::PERSIAN_ROSE:return Color("Persian rose",254,40,162);break;
        case colors::PERSIMMON:return Color("Persimmon",236,88,0);break;
        case colors::PERU:return Color("Peru",205,133,63);break;
        case colors::PHLOX:return Color("Phlox",223,0,255);break;
        case colors::PHTHALO_BLUE:return Color("Phthalo blue",0,15,137);break;
        case colors::PHTHALO_GREEN:return Color("Phthalo green",18,53,36);break;
        case colors::PICTON_BLUE:return Color("Picton blue",69,177,232);break;
        case colors::PICTORIAL_CARMINE:return Color("Pictorial carmine",195,11,78);break;
        case colors::PIGGY_PINK:return Color("Piggy pink",253,221,230);break;
        case colors::PINE_GREEN:return Color("Pine green",1,121,111);break;
        case colors::PINK:return Color("Pink",255,192,203);break;
        case colors::PINK_PANTONE:return Color("Pink (Pantone)",215,72,148);break;
        case colors::PINK_LACE:return Color("Pink lace",255,221,244);break;
        case colors::PINK_LAVENDER:return Color("Pink lavender",216,178,209);break;
        case colors::PINK_ORANGE:return Color("Pink-orange",255,153,102);break;
        case colors::PINK_PEARL:return Color("Pink pearl",231,172,207);break;
        case colors::PINK_SHERBET:return Color("Pink Sherbet",247,143,167);break;
        case colors::PISTACHIO:return Color("Pistachio",147,197,114);break;
        case colors::PLATINUM:return Color("Platinum",229,228,226);break;
        case colors::PLUM:return Color("Plum",142,69,133);break;
        case colors::PLUM_WEB:return Color("Plum (web)",221,160,221);break;
        case colors::POMP_AND_POWER:return Color("Pomp and Power",134,96,142);break;
        case colors::POPSTAR:return Color("Popstar",190,79,98);break;
        case colors::PORTLAND_ORANGE:return Color("Portland Orange",255,90,54);break;
        case colors::POWDER_BLUE:return Color("Powder blue",176,224,230);break;
        case colors::PRINCETON_ORANGE:return Color("Princeton orange",255,143,0);break;
        case colors::PRUNE:return Color("Prune",112,28,28);break;
        case colors::PRUSSIAN_BLUE:return Color("Prussian blue",0,49,83);break;
        case colors::PSYCHEDELIC_PURPLE:return Color("Psychedelic purple",223,0,255);break;
        case colors::PUCE:return Color("Puce",204,136,153);break;
        case colors::PUCE_RED:return Color("Puce red",114,47,55);break;
        case colors::PULLMAN_BROWN_UPS_BROWN:return Color("Pullman Brown (UPS Brown)",100,65,23);break;
        case colors::PUMPKIN:return Color("Pumpkin",255,117,24);break;
        case colors::PURPLE_HTML:return Color("Purple (HTML)",128,0,128);break;
        case colors::PURPLE_MUNSELL:return Color("Purple (Munsell)",159,0,197);break;
        case colors::PURPLE_X11:return Color("Purple (X11)",160,32,240);break;
        case colors::PURPLE_HEART:return Color("Purple Heart",105,53,156);break;
        case colors::PURPLE_MOUNTAIN_MAJESTY:return Color("Purple mountain majesty",150,120,182);break;
        case colors::PURPLE_NAVY:return Color("Purple navy",78,81,128);break;
        case colors::PURPLE_PIZZAZZ:return Color("Purple pizzazz",254,78,218);break;
        case colors::PURPLE_TAUPE:return Color("Purple taupe",80,64,77);break;
        case colors::PURPUREUS:return Color("Purpureus",154,78,174);break;
        case colors::QUARTZ:return Color("Quartz",81,72,79);break;
        case colors::QUEEN_BLUE:return Color("Queen blue",67,107,149);break;
        case colors::QUEEN_PINK:return Color("Queen pink",232,204,215);break;
        case colors::QUINACRIDONE_MAGENTA:return Color("Quinacridone magenta",142,58,89);break;
        case colors::RACKLEY:return Color("Rackley",93,138,168);break;
        case colors::RADICAL_RED:return Color("Radical Red",255,53,94);break;
        case colors::RAJAH:return Color("Rajah",251,171,96);break;
        case colors::RASPBERRY:return Color("Raspberry",227,11,93);break;
        case colors::RASPBERRY_GLACE:return Color("Raspberry glace",145,95,109);break;
        case colors::RASPBERRY_PINK:return Color("Raspberry pink",226,80,152);break;
        case colors::RASPBERRY_ROSE:return Color("Raspberry rose",179,68,108);break;
        case colors::RAW_UMBER:return Color("Raw umber",130,102,68);break;
        case colors::RAZZLE_DAZZLE_ROSE:return Color("Razzle dazzle rose",255,51,204);break;
        case colors::RAZZMATAZZ:return Color("Razzmatazz",227,37,107);break;
        case colors::RAZZMIC_BERRY:return Color("Razzmic Berry",141,78,133);break;
        case colors::RED:return Color("Red",255,0,0);break;
        case colors::RED_CRAYOLA:return Color("Red (Crayola)",238,32,77);break;
        case colors::RED_MUNSELL:return Color("Red (Munsell)",242,0,60);break;
        case colors::RED_NCS:return Color("Red (NCS)",196,2,51);break;
        case colors::RED_PANTONE:return Color("Red (Pantone)",237,41,57);break;
        case colors::RED_PIGMENT:return Color("Red (pigment)",237,28,36);break;
        case colors::RED_RYB:return Color("Red (RYB)",254,39,18);break;
        case colors::RED_BROWN:return Color("Red-brown",165,42,42);break;
        case colors::RED_DEVIL:return Color("Red devil",134,1,17);break;
        case colors::RED_ORANGE:return Color("Red-orange",255,83,73);break;
        case colors::RED_PURPLE:return Color("Red-purple",228,0,120);break;
        case colors::RED_VIOLET:return Color("Red-violet",199,21,133);break;
        case colors::REDWOOD:return Color("Redwood",164,90,82);break;
        case colors::REGALIA:return Color("Regalia",82,45,128);break;
        case colors::RESOLUTION_BLUE:return Color("Resolution blue",0,35,135);break;
        case colors::RHYTHM:return Color("Rhythm",119,118,150);break;
        case colors::RICH_BLACK:return Color("Rich black",0,64,64);break;
        case colors::RICH_BRILLIANT_LAVENDER:return Color("Rich brilliant lavender",241,167,254);break;
        case colors::RICH_CARMINE:return Color("Rich carmine",215,0,64);break;
        case colors::RICH_ELECTRIC_BLUE:return Color("Rich electric blue",8,146,208);break;
        case colors::RICH_LAVENDER:return Color("Rich lavender",167,107,207);break;
        case colors::RICH_LILAC:return Color("Rich lilac",182,102,210);break;
        case colors::RICH_MAROON:return Color("Rich maroon",176,48,96);break;
        case colors::RIFLE_GREEN:return Color("Rifle green",68,76,56);break;
        case colors::ROAST_COFFEE:return Color("Roast coffee",112,66,65);break;
        case colors::ROBIN_EGG_BLUE:return Color("Robin egg blue",0,204,204);break;
        case colors::ROCKET_METALLIC:return Color("Rocket metallic",138,127,128);break;
        case colors::ROMAN_SILVER:return Color("Roman silver",131,137,150);break;
        case colors::ROSE:return Color("Rose",255,0,127);break;
        case colors::ROSE_BONBON:return Color("Rose bonbon",249,66,158);break;
        case colors::ROSE_EBONY:return Color("Rose ebony",103,72,70);break;
        case colors::ROSE_GOLD:return Color("Rose gold",183,110,121);break;
        case colors::ROSE_MADDER:return Color("Rose madder",227,38,54);break;
        case colors::ROSE_PINK:return Color("Rose pink",255,102,204);break;
        case colors::ROSE_QUARTZ:return Color("Rose quartz",170,152,169);break;
        case colors::ROSE_RED:return Color("Rose red",194,30,86);break;
        case colors::ROSE_TAUPE:return Color("Rose taupe",144,93,93);break;
        case colors::ROSE_VALE:return Color("Rose vale",171,78,82);break;
        case colors::ROSEWOOD:return Color("Rosewood",101,0,11);break;
        case colors::ROSSO_CORSA:return Color("Rosso corsa",212,0,0);break;
        case colors::ROSY_BROWN:return Color("Rosy brown",188,143,143);break;
        case colors::ROYAL_AZURE:return Color("Royal azure",0,56,168);break;
        case colors::ROYAL_BLUE:return Color("Royal blue",0,35,102);break;
        case colors::ROYAL_FUCHSIA:return Color("Royal fuchsia",202,44,146);break;
        case colors::ROYAL_PURPLE:return Color("Royal purple",120,81,169);break;
        case colors::ROYAL_YELLOW:return Color("Royal yellow",250,218,94);break;
        case colors::RUBER:return Color("Ruber",206,70,118);break;
        case colors::RUBINE_RED:return Color("Rubine red",209,0,86);break;
        case colors::RUBY:return Color("Ruby",224,17,95);break;
        case colors::RUBY_RED:return Color("Ruby red",155,17,30);break;
        case colors::RUDDY:return Color("Ruddy",255,0,40);break;
        case colors::RUDDY_BROWN:return Color("Ruddy brown",187,101,40);break;
        case colors::RUDDY_PINK:return Color("Ruddy pink",225,142,150);break;
        case colors::RUFOUS:return Color("Rufous",168,28,7);break;
        case colors::RUSSET:return Color("Russet",128,70,27);break;
        case colors::RUSSIAN_GREEN:return Color("Russian green",103,146,103);break;
        case colors::RUSSIAN_VIOLET:return Color("Russian violet",50,23,77);break;
        case colors::RUST:return Color("Rust",183,65,14);break;
        case colors::RUSTY_RED:return Color("Rusty red",218,44,67);break;
        case colors::SACRAMENTO_STATE_GREEN:return Color("Sacramento State green",0,86,63);break;
        case colors::SADDLE_BROWN:return Color("Saddle brown",139,69,19);break;
        case colors::SAFETY_ORANGE_BLAZE_ORANGE:return Color("Safety orange (blaze orange)",255,103,0);break;
        case colors::SAFETY_YELLOW:return Color("Safety yellow",238,210,2);break;
        case colors::SAFFRON:return Color("Saffron",244,196,48);break;
        case colors::SAGE:return Color("Sage",188,184,138);break;
        case colors::ST_PATRICKS_BLUE:return Color("St. Patrick-s blue",35,41,122);break;
        case colors::SALMON:return Color("Salmon",250,128,114);break;
        case colors::SALMON_PINK:return Color("Salmon pink",255,145,164);break;
        case colors::SAND:return Color("Sand",194,178,128);break;
        case colors::SAND_DUNE:return Color("Sand dune",150,113,23);break;
        case colors::SANDSTORM:return Color("Sandstorm",236,213,64);break;
        case colors::SANDY_BROWN:return Color("Sandy brown",244,164,96);break;
        case colors::SANDY_TAUPE:return Color("Sandy taupe",150,113,23);break;
        case colors::SANGRIA:return Color("Sangria",146,0,10);break;
        case colors::SAP_GREEN:return Color("Sap green",80,125,42);break;
        case colors::SAPPHIRE:return Color("Sapphire",15,82,186);break;
        case colors::SAPPHIRE_BLUE:return Color("Sapphire blue",0,103,165);break;
        case colors::SATIN_SHEEN_GOLD:return Color("Satin sheen gold",203,161,53);break;
        case colors::SCARLET:return Color("Scarlet",253,14,53);break;
        case colors::SCHAUSS_PINK:return Color("Schauss pink",255,145,175);break;
        case colors::SCHOOL_BUS_YELLOW:return Color("School bus yellow",255,216,0);break;
        case colors::SCREAMIN_GREEN:return Color("Screamin- Green",118,255,122);break;
        case colors::SEA_BLUE:return Color("Sea blue",0,105,148);break;
        case colors::SEA_GREEN:return Color("Sea green",46,139,87);break;
        case colors::SEAL_BROWN:return Color("Seal brown",50,20,20);break;
        case colors::SEASHELL:return Color("Seashell",255,245,238);break;
        case colors::SELECTIVE_YELLOW:return Color("Selective yellow",255,186,0);break;
        case colors::SEPIA:return Color("Sepia",112,66,20);break;
        case colors::SHADOW:return Color("Shadow",138,121,93);break;
        case colors::SHADOW_BLUE:return Color("Shadow blue",119,139,165);break;
        case colors::SHAMPOO:return Color("Shampoo",255,207,241);break;
        case colors::SHAMROCK_GREEN:return Color("Shamrock green",0,158,96);break;
        case colors::SHEEN_GREEN:return Color("Sheen Green",143,212,0);break;
        case colors::SHIMMERING_BLUSH:return Color("Shimmering Blush",217,134,149);break;
        case colors::SHOCKING_PINK:return Color("Shocking pink",252,15,192);break;
        case colors::SHOCKING_PINK_CRAYOLA:return Color("Shocking pink (Crayola)",255,111,255);break;
        case colors::SIENNA:return Color("Sienna",136,45,23);break;
        case colors::SILVER:return Color("Silver",192,192,192);break;
        case colors::SILVER_CHALICE:return Color("Silver chalice",172,172,172);break;
        case colors::SILVER_LAKE_BLUE:return Color("Silver Lake blue",93,137,186);break;
        case colors::SILVER_PINK:return Color("Silver pink",196,174,173);break;
        case colors::SILVER_SAND:return Color("Silver sand",191,193,194);break;
        case colors::SINOPIA:return Color("Sinopia",203,65,11);break;
        case colors::SKOBELOFF:return Color("Skobeloff",0,116,116);break;
        case colors::SKY_BLUE:return Color("Sky blue",135,206,235);break;
        case colors::SKY_MAGENTA:return Color("Sky magenta",207,113,175);break;
        case colors::SLATE_BLUE:return Color("Slate blue",106,90,205);break;
        case colors::SLATE_GRAY:return Color("Slate gray",112,128,144);break;
        case colors::SMALT_DARK_POWDER_BLUE:return Color("Smalt (Dark powder blue)",0,51,153);break;
        case colors::SMITTEN:return Color("Smitten",200,65,134);break;
        case colors::SMOKE:return Color("Smoke",115,130,118);break;
        case colors::SMOKEY_TOPAZ:return Color("Smokey topaz",147,61,65);break;
        case colors::SMOKY_BLACK:return Color("Smoky black",16,12,8);break;
        case colors::SNOW:return Color("Snow",255,250,250);break;
        case colors::SOAP:return Color("Soap",206,200,239);break;
        case colors::SOLID_PINK:return Color("Solid pink",137,56,67);break;
        case colors::SONIC_SILVER:return Color("Sonic silver",117,117,117);break;
        case colors::SPARTAN_CRIMSON:return Color("Spartan Crimson",158,19,22);break;
        case colors::SPACE_CADET:return Color("Space cadet",29,41,81);break;
        case colors::SPANISH_BISTRE:return Color("Spanish bistre",128,117,50);break;
        case colors::SPANISH_BLUE:return Color("Spanish blue",0,112,184);break;
        case colors::SPANISH_CARMINE:return Color("Spanish carmine",209,0,71);break;
        case colors::SPANISH_CRIMSON:return Color("Spanish crimson",229,26,76);break;
        case colors::SPANISH_GRAY:return Color("Spanish gray",152,152,152);break;
        case colors::SPANISH_GREEN:return Color("Spanish green",0,145,80);break;
        case colors::SPANISH_ORANGE:return Color("Spanish orange",232,97,0);break;
        case colors::SPANISH_PINK:return Color("Spanish pink",247,191,190);break;
        case colors::SPANISH_RED:return Color("Spanish red",230,0,38);break;
        case colors::SPANISH_SKY_BLUE:return Color("Spanish sky blue",0,255,255);break;
        case colors::SPANISH_VIOLET:return Color("Spanish violet",76,40,130);break;
        case colors::SPANISH_VIRIDIAN:return Color("Spanish viridian",0,127,92);break;
        case colors::SPIRO_DISCO_BALL:return Color("Spiro Disco Ball",15,192,252);break;
        case colors::SPRING_BUD:return Color("Spring bud",167,252,0);break;
        case colors::SPRING_GREEN:return Color("Spring green",0,255,127);break;
        case colors::STAR_COMMAND_BLUE:return Color("Star command blue",0,123,184);break;
        case colors::STEEL_BLUE:return Color("Steel blue",70,130,180);break;
        case colors::STEEL_PINK:return Color("Steel pink",204,51,204);break;
        case colors::STIL_DE_GRAIN_YELLOW:return Color("Stil de grain yellow",250,218,94);break;
        case colors::STIZZA:return Color("Stizza",153,0,0);break;
        case colors::STORMCLOUD:return Color("Stormcloud",79,102,106);break;
        case colors::STRAW:return Color("Straw",228,217,111);break;
        case colors::STRAWBERRY:return Color("Strawberry",252,90,141);break;
        case colors::SUNGLOW:return Color("Sunglow",255,204,51);break;
        case colors::SUNRAY:return Color("Sunray",227,171,87);break;
        case colors::SUNSET:return Color("Sunset",250,214,165);break;
        case colors::SUNSET_ORANGE:return Color("Sunset orange",253,94,83);break;
        case colors::SUPER_PINK:return Color("Super pink",207,107,169);break;
        case colors::TAN:return Color("Tan",210,180,140);break;
        case colors::TANGELO:return Color("Tangelo",249,77,0);break;
        case colors::TANGERINE:return Color("Tangerine",242,133,0);break;
        case colors::TANGERINE_YELLOW:return Color("Tangerine yellow",255,204,0);break;
        case colors::TANGO_PINK:return Color("Tango pink",228,113,122);break;
        case colors::TAUPE:return Color("Taupe",72,60,50);break;
        case colors::TAUPE_GRAY:return Color("Taupe gray",139,133,137);break;
        case colors::TEA_GREEN:return Color("Tea green",208,240,192);break;
        case colors::TEA_ROSE:return Color("Tea rose",248,131,121);break;
        case colors::TEAL:return Color("Teal",0,128,128);break;
        case colors::TEAL_BLUE:return Color("Teal blue",54,117,136);break;
        case colors::TEAL_DEER:return Color("Teal deer",153,230,179);break;
        case colors::TEAL_GREEN:return Color("Teal green",0,130,127);break;
        case colors::TELEMAGENTA:return Color("Telemagenta",207,52,118);break;
        case colors::TENN:return Color("Tenne",205,87,0);break;
        case colors::TERRA_COTTA:return Color("Terra cotta",226,114,91);break;
        case colors::THISTLE:return Color("Thistle",216,191,216);break;
        case colors::THULIAN_PINK:return Color("Thulian pink",222,111,161);break;
        case colors::TICKLE_ME_PINK:return Color("Tickle Me Pink",252,137,172);break;
        case colors::TIFFANY_BLUE:return Color("Tiffany Blue",10,186,181);break;
        case colors::TIGERS_EYE:return Color("Tiger-s eye",224,141,60);break;
        case colors::TIMBERWOLF:return Color("Timberwolf",219,215,210);break;
        case colors::TITANIUM_YELLOW:return Color("Titanium yellow",238,230,0);break;
        case colors::TOMATO:return Color("Tomato",255,99,71);break;
        case colors::TOOLBOX:return Color("Toolbox",116,108,192);break;
        case colors::TOPAZ:return Color("Topaz",255,200,124);break;
        case colors::TRACTOR_RED:return Color("Tractor red",253,14,53);break;
        case colors::TROLLEY_GREY:return Color("Trolley Grey",128,128,128);break;
        case colors::TROPICAL_RAIN_FOREST:return Color("Tropical rain forest",0,117,94);break;
        case colors::TRUE_BLUE:return Color("True Blue",0,115,207);break;
        case colors::TUFTS_BLUE:return Color("Tufts Blue",65,125,193);break;
        case colors::TULIP:return Color("Tulip",255,135,141);break;
        case colors::TUMBLEWEED:return Color("Tumbleweed",222,170,136);break;
        case colors::TURKISH_ROSE:return Color("Turkish rose",181,114,129);break;
        case colors::TURQUOISE:return Color("Turquoise",64,224,208);break;
        case colors::TURQUOISE_BLUE:return Color("Turquoise blue",0,255,239);break;
        case colors::TURQUOISE_GREEN:return Color("Turquoise green",160,214,180);break;
        case colors::TUSCAN:return Color("Tuscan",250,214,165);break;
        case colors::TUSCAN_BROWN:return Color("Tuscan brown",111,78,55);break;
        case colors::TUSCAN_RED:return Color("Tuscan red",124,72,72);break;
        case colors::TUSCAN_TAN:return Color("Tuscan tan",166,123,91);break;
        case colors::TUSCANY:return Color("Tuscany",192,153,153);break;
        case colors::TWILIGHT_LAVENDER:return Color("Twilight lavender",138,73,107);break;
        case colors::TYRIAN_PURPLE:return Color("Tyrian purple",102,2,60);break;
        case colors::UA_BLUE:return Color("UA blue",0,51,170);break;
        case colors::UA_RED:return Color("UA red",217,0,76);break;
        case colors::UBE:return Color("Ube",136,120,195);break;
        case colors::UCLA_BLUE:return Color("UCLA Blue",83,104,149);break;
        case colors::UCLA_GOLD:return Color("UCLA Gold",255,179,0);break;
        case colors::UFO_GREEN:return Color("UFO Green",60,208,112);break;
        case colors::ULTRAMARINE:return Color("Ultramarine",18,10,143);break;
        case colors::ULTRAMARINE_BLUE:return Color("Ultramarine blue",65,102,245);break;
        case colors::ULTRA_PINK:return Color("Ultra pink",255,111,255);break;
        case colors::ULTRA_RED:return Color("Ultra red",252,108,133);break;
        case colors::UMBER:return Color("Umber",99,81,71);break;
        case colors::UNBLEACHED_SILK:return Color("Unbleached silk",255,221,202);break;
        case colors::UNITED_NATIONS_BLUE:return Color("United Nations blue",91,146,229);break;
        case colors::UNIVERSITY_OF_CALIFORNIA_GOLD:return Color("University of California Gold",183,135,39);break;
        case colors::UNMELLOW_YELLOW:return Color("Unmellow yellow",255,255,102);break;
        case colors::UP_FOREST_GREEN:return Color("UP Forest green",1,68,33);break;
        case colors::UP_MAROON:return Color("UP Maroon",123,17,19);break;
        case colors::UPSDELL_RED:return Color("Upsdell red",174,32,41);break;
        case colors::UROBILIN:return Color("Urobilin",225,173,33);break;
        case colors::USAFA_BLUE:return Color("USAFA blue",0,79,152);break;
        case colors::USC_CARDINAL:return Color("USC Cardinal",153,0,0);break;
        case colors::USC_GOLD:return Color("USC Gold",255,204,0);break;
        case colors::UNIVERSITY_OF_TENNESSEE_ORANGE:return Color("University of Tennessee Orange",247,127,0);break;
        case colors::UTAH_CRIMSON:return Color("Utah Crimson",211,0,63);break;
        case colors::VANILLA:return Color("Vanilla",243,229,171);break;
        case colors::VANILLA_ICE:return Color("Vanilla ice",243,143,169);break;
        case colors::VEGAS_GOLD:return Color("Vegas gold",197,179,88);break;
        case colors::VENETIAN_RED:return Color("Venetian red",200,8,21);break;
        case colors::VERDIGRIS:return Color("Verdigris",67,179,174);break;
        case colors::VERMILION:return Color("Vermilion",227,66,52);break;
        case colors::VERONICA:return Color("Veronica",160,32,240);break;
        case colors::VIOLET:return Color("Violet",143,0,255);break;
        case colors::VIOLET_COLOR_WHEEL:return Color("Violet (color wheel)",127,0,255);break;
        case colors::VIOLET_RYB:return Color("Violet (RYB)",134,1,175);break;
        case colors::VIOLET_WEB:return Color("Violet (web)",238,130,238);break;
        case colors::VIOLET_BLUE:return Color("Violet-blue",50,74,178);break;
        case colors::VIOLET_RED:return Color("Violet-red",247,83,148);break;
        case colors::VIRIDIAN:return Color("Viridian",64,130,109);break;
        case colors::VIRIDIAN_GREEN:return Color("Viridian green",0,150,152);break;
        case colors::VIVID_AUBURN:return Color("Vivid auburn",146,39,36);break;
        case colors::VIVID_BURGUNDY:return Color("Vivid burgundy",159,29,53);break;
        case colors::VIVID_CERISE:return Color("Vivid cerise",218,29,129);break;
        case colors::VIVID_ORCHID:return Color("Vivid orchid",204,0,255);break;
        case colors::VIVID_SKY_BLUE:return Color("Vivid sky blue",0,204,255);break;
        case colors::VIVID_TANGERINE:return Color("Vivid tangerine",255,160,137);break;
        case colors::VIVID_VIOLET:return Color("Vivid violet",159,0,255);break;
        case colors::WARM_BLACK:return Color("Warm black",0,66,66);break;
        case colors::WATERSPOUT:return Color("Waterspout",164,244,249);break;
        case colors::WENGE:return Color("Wenge",100,84,82);break;
        case colors::WHEAT:return Color("Wheat",245,222,179);break;
        case colors::WHITE:return Color("White",255,255,255);break;
        case colors::WHITE_SMOKE:return Color("White smoke",245,245,245);break;
        case colors::WILD_BLUE_YONDER:return Color("Wild blue yonder",162,173,208);break;
        case colors::WILD_ORCHID:return Color("Wild orchid",212,112,162);break;
        case colors::WILD_STRAWBERRY:return Color("Wild Strawberry",255,67,164);break;
        case colors::WILD_WATERMELON:return Color("Wild watermelon",252,108,133);break;
        case colors::WILLPOWER_ORANGE:return Color("Willpower orange",253,88,0);break;
        case colors::WINDSOR_TAN:return Color("Windsor tan",167,85,2);break;
        case colors::WINE:return Color("Wine",114,47,55);break;
        case colors::WINE_DREGS:return Color("Wine dregs",103,49,71);break;
        case colors::WISTERIA:return Color("Wisteria",201,160,220);break;
        case colors::WOOD_BROWN:return Color("Wood brown",193,154,107);break;
        case colors::XANADU:return Color("Xanadu",115,134,120);break;
        case colors::YALE_BLUE:return Color("Yale Blue",15,77,146);break;
        case colors::YANKEES_BLUE:return Color("Yankees blue",28,40,65);break;
        case colors::YELLOW:return Color("Yellow",255,255,0);break;
        case colors::YELLOW_CRAYOLA:return Color("Yellow (Crayola)",252,232,131);break;
        case colors::YELLOW_MUNSELL:return Color("Yellow (Munsell)",239,204,0);break;
        case colors::YELLOW_NCS:return Color("Yellow (NCS)",255,211,0);break;
        case colors::YELLOW_PANTONE:return Color("Yellow (Pantone)",254,223,0);break;
        case colors::YELLOW_PROCESS:return Color("Yellow (process)",255,239,0);break;
        case colors::YELLOW_RYB:return Color("Yellow (RYB)",254,254,51);break;
        case colors::YELLOW_GREEN:return Color("Yellow-green",154,205,50);break;
        case colors::YELLOW_ORANGE:return Color("Yellow Orange",255,174,66);break;
        case colors::YELLOW_ROSE:return Color("Yellow rose",255,240,0);break;
        case colors::ZAFFRE:return Color("Zaffre",0,20,168);break;
        case colors::ZINNWALDITE_BROWN:return Color("Zinnwaldite brown",44,22,8);break;
        case colors::ZOMP:return Color("Zomp",57,167,142);break;
        case colors::RANDOM:return createRandomColor();break;
        case colors::RANDOM_LIGHT:return createRandomLightColor();break;
        case colors::RANDOM_DARK:return createRandomDarkColor();break;
        case colors::INVISIBLE:
        case colors::TRANSPARENT:return Color("Transparent",0,0,0,255);break;
    default:break;

    }
    std::cerr<<"Could not find "<<color<<std::endl;
    return Color();
}

Color ColorFactory::create(const float &r, const float &g, const float &b, const float &a)
{
    return Color(r*255.0f,g*255.0f,b*255.0f,a*255.0f);
}

Color ColorFactory::createNextColor()
{
    Color color = create(colors::NEXT_COLOR);
    int c=colors::NEXT_COLOR;c++;
    colors::NEXT_COLOR = (colors::ColorType(c));
    if(colors::NEXT_COLOR == colors::NUM_COLORS)
    {
        colors::NEXT_COLOR = colors::ColorType(0);
    }
    return color;
}

Color ColorFactory::createRandomNamedColor()
{

    return create((colors::ColorType)m_colorRng.next((int)colors::RED,(int)colors::NUM_COLORS-1));
}

Color ColorFactory::createRandomColor()
{
    return Color("Random Color",m_colorRng.next(255),m_colorRng.next(255),m_colorRng.next(255),255);
}

Color ColorFactory::createRandomDarkColor()
{
    return Color("Random Dark Color",50+m_colorRng.next(100),50+m_colorRng.next(100),50+m_colorRng.next(100),255);
}

Color ColorFactory::createRandomLightColor()
{
    return Color("Random Light Color",m_colorRng.next(150,255),m_colorRng.next(150,255),m_colorRng.next(150,255),255);
}

void ColorFactory::resetNextColor()
{
    colors::NEXT_COLOR=colors::ColorType(0);
}

}}}//namespace
