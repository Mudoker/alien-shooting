#include "../header/global.h"

// OS trademark structure
Information OS_INFO = {
    .ASCII_ART_LOGO_TEXT = "",
    .ASCII_ART_LOGO = "",
    .OS_VERSION = "0.0.1",
    .OS_NAME = "",
    .OS_ID = "",
    .CREATED_AT = "2024-04-20",
    .UPDATED_AT = "2024-04-28",

    // Prompt text
    .PROMPT = "BrightOS> ",

    // Author
    .AUTHOR_NAME = "Quoc Doan",
    .AUTHOR_USERNAME = "Mudoker",
    .AUTHOR_EMAIL = "huuquoc7603@gmail.com",
    .AUTHOR_SID = "S3927776",
    .AUTHOR_GITHUB_URL = "https://github.com/Mudoker",

    // Acknowledgement
    .ACK_SCHOOL = "RMIT University",
    .ACK_COURSE = "EEET2490: Embedded System: OS and Interfacing",
    .ACK_LECTURER = "Mr Linh T.D.",
    .ACK_SUBMITTED_BY = "Quoc Doan",
    .ACK_DECLARATION =
        "I declare that in submitting all work for this assessment "
        "I have read, understood and agree to the content and "
        "expectations of the Assessment declaration.",
};

// BrightOS theme configuration
Theme THEME = {
    .PRIMARY_COLOR = "\033[0;33m",
    .SECONDARY_COLOR = "\033[0m",
    .BACKGROUND_COLOR = "\x1b[49m",
    .SUCCESS_COLOR = "\033[0;32m",
    .ERROR_COLOR = "\033[0;31m",
};

