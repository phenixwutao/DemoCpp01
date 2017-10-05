#pragma once

#ifndef __MODERN_CPP_H
#define __MODERN_CPP_H

#define FUNC_INFO (printf("-------------------- Function %s --------------------\n", __func__));
#define PASS_INFO(k) (printf("---------- Pass %u ----------\n", k));

void ModernCppDemoAuto();
void ModernCppDemoAlias();
void ModernCppDemoInitializerList();
void ModernCppDemoNonStaticMemberInitialization();
void ModernCppDemoAlignment();
void ModernCppDemoScopedEnumerations();
void ModernCppDemoOverride_Final_For_Virtual_Methods();
void ModernCppDemoRangeBasedForLoop();
void ModernCppDemoEnableRangeBasedForLoop4CustomTypes();
void ModernCppDemoCheckModules();
void ModernCppDemoExplicitConstructorAndConversionOperator();
void ModernCppDemoNamespace();
void ModernCppDemoNamespacesForSymbolVersioning();
void ModernCppDemoStructuredBindings();


#endif
