%% Project Euler Problem 852

%% Game Parameters
N = 1; % Number of fair and unfair coins
P_unfairHeads = 0.75; % Unfair coin heads probability
% Score adjustments for winning, losing, and flipping
winScore = 20;
loseScore = -50;
flipPenalty = 1;

%% Expected Score Calculation
gameScore = 0;
fairCount = N; unfairCount = N;

for n = 1:(2*N)
    coinType = 1; % Fair
    if randi(fairCount + unfairCount) > fairCount
        coinType = 0; % Unfair
    end

    P_fair = fairCount / (fairCount + unfairCount);
    P_unfair = 1 - P_fair;

    flipping = true; flipCount = uint32(0);
    E_curr = max(P_fair, P_unfair) * winScore + min(P_fair, P_unfair) * loseScore;

    roundExpectedScore = calcExpectedScore(0, E_curr, 1, [0, 0], P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty);

    disp("Current distribution: " + fairCount + " fair, " + unfairCount + " unfair");
    disp("Expected score: " + roundExpectedScore);
    gameScore = gameScore + roundExpectedScore;

    if coinType < 1
        unfairCount = unfairCount - 1;
    else
        fairCount = fairCount - 1;
    end
end

fprintf("Final expected score: %.6f\n",gameScore)

function roundExpectedScore = calcExpectedScore(roundExpectedScore, E_curr, P_curr, seq, P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty)

fprintf('Sequence (H, T): [%d, %d]\n',seq(1),seq(2));
disp("E_curr: " + E_curr)
disp("P_curr: " + P_curr)

[P_sequenceH, E_sequenceH] = sequenceProbabilityAndGuessScore(...
            [seq(1) + 1, seq(2)], P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty);

disp("E_AddHeads: " + E_sequenceH)

[P_sequenceT, E_sequenceT] = sequenceProbabilityAndGuessScore(...
            [seq(1), seq(2) + 1], P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty);

disp("E_AddTails: " + E_sequenceT)

E_flip = P_sequenceH/(P_sequenceH + P_sequenceT) * E_sequenceH + ...
     P_sequenceT/(P_sequenceH + P_sequenceT) * E_sequenceT;

% E_flip = (0.5) * E_sequenceH + ... 
%      (0.5) * E_sequenceT;

% disp("E_Flip: " + E_flip)

if E_flip > E_curr % Strategy 1 - Expected flip value
%if sum(seq) < 8 % Strategy 2 - Only certain number of flips
%if (E_curr < E_sequenceT || E_curr < E_sequenceH) && P_curr > 1e-12 % Strategy 3 - If a better option exists (and this isn't super minor), flip
    disp("Flipping again!")
    roundExpectedScore = roundExpectedScore + calcExpectedScore(roundExpectedScore, E_sequenceH, P_sequenceH, [seq(1) + 1, seq(2)], P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty) + ...
    calcExpectedScore(roundExpectedScore, E_sequenceT, P_sequenceT, [seq(1), seq(2) + 1], P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty);
else
    disp("Stopping here!") 
    roundExpectedScore = roundExpectedScore + E_curr * P_curr;
    disp("Adding " + E_curr * P_curr + " to expected score.")
end
    
end

% This function calculates the probability of a given sequence, and the
% expected score if you guess the most likely coin (unfair or fair) after
% getting this sequence
function [P_sequence, E_sequence] = sequenceProbabilityAndGuessScore(...
    sequence, P_fair, P_unfair, P_unfairHeads, winScore, loseScore, flipPenalty)

P_sequenceFair = P_fair * 0.5 ^ (sequence(1) + sequence(2));
P_sequenceUnfair = P_unfair * P_unfairHeads ^ sequence(1) * (1 - P_unfairHeads) ^ sequence(2);

P_sequence = P_sequenceFair +  P_sequenceUnfair;

E_sequence = max(P_sequenceFair, P_sequenceUnfair)/P_sequence * winScore + ...
    min(P_sequenceFair, P_sequenceUnfair)/P_sequence * loseScore;
E_sequence = E_sequence - flipPenalty*sum(sequence);
end