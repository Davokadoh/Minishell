# 42 Minishell

### Aussi mignon qu’un vrai shell

## Auteurs:  [Davokadoh](https://github.com/Davokadoh) && [BlaiseK](https://github.com/blaisek)

### Menu
* [Fonctions externes autorises](Fonctions-externes-autorises)
* [Description](#description)
* [Introduction](#introduction)
* [Structure du Projet](Structure-du-Projet)
  *  [Prompt](Prompt)
	*  [Lexer](Lexer)
	*  [Parser](Parser)
  *  [Expander](Expander)
	*  [Executor](Executor)
* [Schema](Schema)
* [Resources](Resources)

## Fonctions externes autorises


![Fonctions externes](https://github.com/blaisek/Minishell/blob/main/Fonctions%20externes.png)

## Description

Le but du projet est de recréer plusieurs fonctionnalitées d'un Shell.

## Introduction

L’existence des shells est intrinsèquement liée à celle de l’informatique.
À l’époque, les développeurs étaient tous d’accord pour dire que communiquer avec
un ordinateur en utilisant des interrupteurs 1/0 était fortement irritant.
La suite logique fut d’inventer un moyen de communiquer via des lignes de commandes
interactives dans un langage jusqu’à un certain point proche du langage humain.
Avec Minishell, vous allez voyager dans le passé et faire face aux problèmes que l’on
pouvait avoir au temps où Windows n’existait pas encore

## Structure du Projet

Nous avons subdivisé le projet en plusieurs modules

### Prompt

Le Prompt attend une nouvelle commande et permet d'acceder a l'hisorique de ce qui a ete envoye au lexer

### Lexer
un analyseur lexical ou lexer prend les caractères d'entrée et
rassemble ces caractères en mots appelés jetons.

### Parser
L'analyseur syntaxique ou parser , récupere la sortie du lexer et la met
dans une structure de données appelée Command Table qui stockera les commandes et les arguments qui seront
exécuté.

### Expander

L'expandeur prendra les jetons du parser comme argument.<br>
L'expandeur interprétera les variables d'environnement dans leur valeur correspondante.<br>
Il gère également les sous-shells et toutes les redirections.<br>
Les sous-shells sont exécutés en créant un processus enfant qui exécute un minishell sans readline lisant l'entrée, mais en lui transmettant directement les commandes correctes et non analysées. Et une fois l'analyseur lexical terminé, il appellera l'analyseur syntaxique et ainsi de suite.<br>
Après avoir passé chacune de ces parties sans erreur, il appelle l'exécuteur dans une boucle et donne à l'exécuteur les valeurs correctes avec lesquelles travailler.<br>
Après un appel de l'exécuteur, une valeur d'erreur, similaire à errno, est définie sur le code de sortie de l'exécuteur.<br>
Cette valeur d'erreur peut être vérifiée en exécutant `echo $?` et est utilisée pour la logique `&&` et `||`.<br><br>
C'est ainsi que les données sont stockées dans les jetons d'extension et transmises à l'exécuteur

### Executor

L'exécuteur fait comme son nom l'indique , il exécute la commande.<br>
Si la commande donnée est un builtin, elle exécutera simplement la commande dans le même processus, si ce n'est pas le cas, elle créera un processus enfant pour exécuter cette commande.<br>
Une fois que cela est décidé, les redirections d'entrée et de sortie sont effectuées et la commande est exécutée.<br>
L'exécuteur renvoie toujours le code de sortie de tout ce qu'il a fait.<br>

### Schema
![Graphique](https://github.com/blaisek/Minishell/blob/main/Diagramme%20Minishell.drawio.png)

### Resources
[Bash manual](https://www.gnu.org/software/bash/manual/bash.html)

[shell command](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html)

[Writing your shell](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)
