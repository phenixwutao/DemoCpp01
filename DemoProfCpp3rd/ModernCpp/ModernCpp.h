#pragma once

#ifndef __MODERN_CPP_H
#define __MODERN_CPP_H

#define FUNC_INFO (printf("-------------------- Function %s --------------------\n", __func__));
#define PASS_INFO(k) (printf("---------- Pass %u ----------\n", k));

void Ch01_DemoAuto();
void Ch01_DemoAlias();
void Ch01_DemoInitializerList();
void Ch01_DemoNonStaticMemberInitialization();
void Ch01_DemoAlignment();
void Ch01_DemoScopedEnumerations();
void Ch01_DemoOverride_Final_For_Virtual_Methods();
void Ch01_DemoRangeBasedForLoop();
void Ch01_DemoEnableRangeBasedForLoop4CustomTypes();
void Ch01_DemoCheckModules();
void Ch01_DemoExplicitConstructorAndConversionOperator();
void Ch01_DemoNamespace();
void Ch01_DemoNamespacesForSymbolVersioning();
void Ch01_DemoStructuredBindings();

void Ch02_DemoConvertingNumericStringTypes();
void Ch02_DemoNumberLimitsOtherProperties();
void Ch02_DemoGeneratingPseudoRandomNumbers();
void Ch02_DemoMonteCarloSimulation();



#endif
