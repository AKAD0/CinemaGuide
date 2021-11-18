#include "gtest/gtest.h"
#include "user_account.cpp"

TEST(Gosha_Norm, ok) {
	std::stringstream input;
	std::stringstream output;
	input << "Gogsaee23@mail.ru\n Gosha\n Ivanov\n\0";
	run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Gogsaee23@mail.ru";
    outwq += '\0';
    outwq += "Gosha";
    outwq += '\0';
    outwq += "Ivanov";
    outwq += '\0';
	EXPECT_EQ(outwq == out,1);
}

TEST(Omar_Norm, ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra@mail.ru\n Omar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Dijkstra@mail.ru";
    outwq += '\0';
    outwq += "Omar";
    outwq += '\0';
    outwq += "Yunusov";
    outwq += '\0';
    assert(outwq == out);
}

TEST(Email_ne_Norm, not_ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dij////kstra\n Omar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    EXPECT_EQ(outwq == out,1);
}

TEST(Oma1r_ne_Norm, not_ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra@mail.ru\n Om1ar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}

TEST(Yu1nusov_ne_Norm, not_ok){
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra@mail.ru\n Omar\n Yu1nusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}
TEST(Not_dot, not_ok){
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra@mailru\n Omar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}
TEST(Not_at, not_ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra!mail.ru\n Omar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}
TEST(Omar_slash_ne_norm, not_ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra\n Om///ar\n Yunusov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}
TEST(Yunusov_vopros_ne_norm, not_ok) {
    std::stringstream input;
    std::stringstream output;
    input << "Dijkstra\n Omar\n Yu&n???usov\n\0";
    run( input, output );
    std::string out = output.str(); 
    std::string outwq = "Error related to the authentication of input data.";
    assert(outwq == out);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
