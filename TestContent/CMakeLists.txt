### This file is automatically generated by Qt Design Studio.
### Do not change



qt_add_library(TestContent STATIC)
qt6_add_qml_module(TestContent
    URI "TestContent"
    VERSION 1.0
    RESOURCE_PREFIX "/qt/qml"
    QML_FILES
        "App.qml"
        "pages/SavePage.qml"
        "pages/SelectFilePage.qml"
        "modals/ErrorModal.qml"
        "modals/WaitModal.qml"
        "modals/CustomModal.qml"
        "widgets/FileDelegate.qml"
        "widgets/CustomButton.qml"
        "widgets/BackButton.qml"
    RESOURCES
        "images/tabler--mood-empty.svg"
)


