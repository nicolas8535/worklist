<div id="update-budget">
    <form method="post" action = "">
        <label for="budget-amount" class="info-label">Budget: </label><br/>
            $<?php echo $budget->amount; ?>
            <br/>
        <label for="budget-reason" class="info-label">For: </label><br/>
            <?php 
                if ($budgetClosed == 1) {
                    echo $budget->reason; 
                } else {
            ?>
            <input type="text" id="budget-reason" name="budget-reason" value="<?php echo $budget->reason; ?>"/>
            <?php } ?>
            <br/>
            <?php if (strpos(BUDGET_AUTHORIZED_USERS, "," . $reqUserId . ",") !== false &&
                    $budget->seed == 1) { ?>
            <label for="budget-source" class="info-label">Source: </label>
            <div class="budget-source">
                <?php echo $budget->source_data; ?>
            </div>
            <?php 
                } 
                if ($budget->seed == 0) { ?>
        <label for="budget-source" class="info-label">Source: </label>
        <div class="budget-source">
            <?php echo $budget->source_data . " (" . $sourceBudgetReason . ")"; ?> 
        </div>
            <?php } ?>
            <input type="hidden" id="budget-receiver" name="receiver_id" value="<?php echo $user->getId(); ?>" />
        <br/>
        <label for="budget-note" class="info-label">Note: </label><br/>
            <?php 
                if ($budgetClosed == 1) {
                    echo $budget->notes; 
                } else {
            ?>
                <textarea id="budget-note" name="budget-note"><?php echo $budget->notes; ?></textarea>
            <?php } ?>
        <br/>
        <input type="button" value="<?php echo ($budgetClosed == 1) ? "Close" : "Update"; ?>" id="<?php echo ($budgetClosed == 1) ? "closeButton" : "updateButton"; ?>" />
        <?php if ($budget->active == 1){ ?>
            <input type="button" value="Close Out" id="closeOutButton" />
        <?php } ?>
    </form>
    <?php
    if (isset($_SESSION['userid']) && isset($_SESSION['is_runner']) && $_SESSION['is_runner']) {
        if (!isset($user)) {
            $user = new User();
            $user->findUserById($_SESSION['userid']);
        }
    ?>
        <div>
            <table id="be-table">
                <tr>
                    <td class="be-table_cell1 iToolTip budgetRemaining"><strong>Remaining Funds:</strong></td>
                    <td class="be-table_cell2 iToolTip budgetRemaining"><strong>
                    <?php echo(money_format('$ %i', $remaining)); ?></strong></td>
                </tr>
                <tr>
                    <td onclick="Budget.budgetExpand(0,<?php echo $budget->id; ?>)" class="be-table_cell1 iToolTip budgetAllocated">Allocated:</td>
                    <td onclick="Budget.budgetExpand(0,<?php echo $budget->id; ?>)" class="be-table_cell2 iToolTip budgetAllocated">
                    <?php echo(money_format('$ %i', $allocated)); ?></td>
                </tr>
                <tr>
                    <td onclick="Budget.budgetExpand(1,<?php echo $budget->id; ?>)" class="be-table_cell1 iToolTip budgetSubmitted">Submitted:</td>
                    <td onclick="Budget.budgetExpand(1,<?php echo $budget->id; ?>)" class="be-table_cell2 iToolTip budgetSubmitted">
                    <?php echo(money_format('$ %i', $submitted)); ?></td>
                </tr>
                <tr>
                    <td onclick="Budget.budgetExpand(2,<?php echo $budget->id; ?>)" class="be-table_cell1 iToolTip budgetPaid">Paid:</td>
                    <td onclick="Budget.budgetExpand(2,<?php echo $budget->id; ?>)" class="be-table_cell2 iToolTip budgetPaid">
                    <?php echo(money_format('$ %i', $paid)); ?></td>
                </tr>
                <tr>
                    <td onclick="Budget.budgetExpand(3,<?php echo $budget->id; ?>)" class="be-table_cell1 iToolTip budgetTransfered">Transferred:</td>
                    <td onclick="Budget.budgetExpand(3,<?php echo $budget->id; ?>)" class="be-table_cell2 iToolTip budgetTransfered">
                    <?php echo(money_format('$ %i', $transfered)); ?></td>
                </tr>
            </table>
        </div>
    <?php } ?>
    
</div><!-- end of give budget div-->
