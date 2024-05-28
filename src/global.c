#include "../header/global.h"

// OS trademark structure
Information OS_INFO = {
    .ASCII_ART_LOGO_TEXT =
        "  ______ _______ ___   _     ______   ______  _____  "
        "______ _     _ _______\n"
        "   ____/ |______ |  \\  |     |_____] |_____/    |   |  "
        "____ |_____|    |\n"
        "  /_____ |______ |   \\_|     |_____] |     \\_ __|__ "
        "|_____| |     |    |\n",
    .ASCII_ART_LOGO =

        "                                                         mrrm\n"
        "                                                         rrrr\n"
        "                                                         mrrrr\n"
        "                                                        rrrrrm\n"
        "                                                        mrrrrrr\n"
        "                                                       mrrrrrrrr\n"
        "                                                      rrrrrrrrrrr\n"
        "                                                     rrrrrrrrrrrrrm\n"
        "                         mrrr                      rrrrrrrrrrrrrrrrrr "
        "                     rrr\n"
        "                         rrrrrr                  "
        "rrrrrrrrrrrrrrrrrrrrrr                 rrrrrrm\n"
        "                           rrrrrrrrm       "
        "imrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrmm      mmrrrrrrrr\n"
        "                            "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                             "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                              "
        "rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrrrrrr              "
        "rrrrrrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrrrrm                     "
        " rrrrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrrr                        "
        "   mrrrrrrrrrrrrrrr\n"
        "                               rrrrrrrrrrrrrr                         "
        "     rrrrrrrrrrrrrr\n"
        "                              rrrrrrrrrrrrr                           "
        "      rrrrrrrrrrrrrm\n"
        "                              rrrrrrrrrrrr                            "
        "        rrrrrrrrrrrr\n"
        "                             rrrrrrrrrrrr                             "
        "         rrrrrrrrrrrr\n"
        "                            rrrrrrrrrrrrr                             "
        "         rrrrrrrrrrrrr\n"
        "                          mrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrm\n"
        "                        rrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrr\n"
        "                    rrrrrrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrrrrrm\n"
        "                mrrrrrrrrrrrrrrrrrrrrrrr                              "
        "          rrrrrrrrrrrrrrrrrrrrrrrm\n"
        "\n"
        "\n"
        "\n"
        "                     rrrrrrrrrrrr   mrrrrrrrrrrrrr  rrrrm "
        "rrrrrrrrrrrr  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrmrrrrrrrrr  mrrrrrrrrrrrrrr "
        "rrrrmrrrrrrrrrrrrm  rrrr      rrrrmrrrrrrrrrrrrr\n"
        "                     rrrm     mrrri mrrrr      mrrr rrrrirrrrm        "
        "  rrrmiiiiiirrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrrrrrrrrrrrr rrrrmrrrrm     "
        "mrrm rrrrrrrrrrrrrrr    mrrrr\n"
        "                     rrrm       rrrrmrrrrrrmrrrrrr  rrrrirrrrm     "
        "mrrm rrrr      rrrrr    rrrrr\n"
        "                     rrrrrrrrrrrrrrrmrrrr      rrrr "
        "rrrrirrrrrrrrrrmrrm rrrr      rrrrr    mrrrr\n"
        "                     rrrrrrrrrrrrrr mrrrr       rrrmrrrri  "
        "rrrrrrrrrrrm rrrm      rrrrm    mrrrm\n",
    .OS_VERSION = "0.0.1",
    .OS_NAME = "Bright OS Administrator",
    .OS_ID = "BOS-001",
    .CREATED_AT = "2024-04-05",
    .UPDATED_AT = "2024-04-05",

    // Prompt text
    .PROMPT = "BrightOS> ",

    // Acknowledgement
    .ACK_SCHOOL = "RMIT University",
    .ACK_COURSE = "EEET2490: Embedded System: OS and Interfacing",
    .ACK_LECTURER = "Mr Linh T.D.",
    .ACK_SUBMITTED_BY = "Group 10",
    .ACK_DECLARATION =
        "I declare that in submitting all work for this assessment "
        "I have read, understood and agree to the content and "
        "expectations of the Assessment declaration.",
};

// Team information structure
Team TEAM_X = {
    .TEAM_NAME = "Team 10",
    .TEAM_ID = "10",

    // Team members
    .MEMBERS =
        {
            {
                .NAME = "Quoc Doan",
                .SID = "s3927776",
                .GITHUB = "https://github.com/Mudoker",
                .CONTRIBUTION = "25%",
            },
            {
                .NAME = "Viet Nguyen",
                .SID = "s3927291",
                .GITHUB = "https://github.com/felix101003",
                .CONTRIBUTION = "25%",
            },
            {
                .NAME = "Anh Tran",
                .SID = "s3916566",
                .GITHUB = "https://github.com/Mudoker",
                .CONTRIBUTION = "25%",
            },
            {
                .NAME = "Kim Seokyung",
                .SID = "s3939114",
                .GITHUB = "https://github.com/Mudoker",
                .CONTRIBUTION = "25%",
            },
        },
};

// BrightOS theme configuration
Theme THEME = {
    .PRIMARY_COLOR = "\033[0;33m",
    .SECONDARY_COLOR = "\033[0m",
    .BACKGROUND_COLOR = "\x1b[49m",
    .SUCCESS_COLOR = "\033[0;32m",
    .ERROR_COLOR = "\033[0;31m",
};
