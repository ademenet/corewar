# corewar

Un jeu pour le XXIème siècle.

## Consignes pour le travail sur git :

Il faut partir de la branche `dev` et créer sa propre branche à partir de là. Le mieux serait de faire une branche par personne par features.

Je m'explique : par exemple, je bosse sur le lexer de l'assembleur, je crée une branche `login-lexer` (ou quelque chose dans le genre). Lorsque la feature est prête à être mergé, on la merge dans `dev`.

La branche `dev` permet de recevoir tous les merges et devrait être globalement exempt de bugs (au maximum afin de faciliter l'intégration des features).

En fait, on a un truc comme suit :

```
master
  \___dev
  |    |___asm
  |    |    \___login-feature
  |    |    \___logine2-feature2
  |    |___vm
  |         \___...
  |___example
```

## Messages de commits :

Un petit guide pour qu'on puisse faire des commits avec des messages parlant.

On peut utiliser ce schéma : `<type>(<scope>): <descrition>`

Explications :-) :

- type : c'est le type de travail auquel répond le commit, soit : bug (si on fixe un bug, feat pour une nouvelle feature, test, etc.) ; un verbe d'action le plus souvent ;
- scope : si besoin de préciser dans quelle fonction se trouve les modifications (si important) ;
- description : une rapide description du contexte pour qu'on puisse comprendre d'où ce commit sort.

## Naming des fonctions :

Les fonctions du **corewar** devront commencer par `cw_nomdelafonction`. Cela afin d'éviter que deux fonctions aient le même nom dans la **libft** et **corewar**.
