#include "../header/global.h"

// OS trademark structure
Information OS_INFO = {
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
    .ACK_SUBMITTED_BY = "Team 10",
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